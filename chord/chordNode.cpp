//
//  chordNode.cpp
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "chordNode.hpp"

namespace CHORD {
    //implements constructor
    chordNode::chordNode(std::string _hostname, int _portno, std::string _machine_name) {
        DEBUG_PRINT("Creating chordNode");
        thisNode.hostname = _hostname;
        thisNode.machine_name = _machine_name;
        thisNode.identifier = getHashcode(_machine_name);
        thisNode.portno = _portno;
        
        gotDetectNodeResponse = initiated = false;
        
        //initiate messager pool
        for (int i = 0; i < CHORDNODE_MESSAGER_POOL_SIZE; ++i) {
            messagerPool[i].makeFree();
            messagerPool[i].setPortno(i + CHORDNODE_PORT_OFFSET);
        }
        
        //initiate fingertable entries
        for (int i = 1; i <= IDENTIFIER_LEN; ++i) {
            finger[i].start = (thisNode.identifier + (identifier_t)pow(2, i - 1)) % ((identifier_t)pow(2, IDENTIFIER_LEN));
        }
    }
    
    chordNode::~chordNode() {
        //leave the network
        leave();
    }
    
    void chordNode::dumpFingerTable() {
        for (int i = 1; i <= IDENTIFIER_LEN; ++i) {
            printf("Finger %d:%s\n", i, finger[i].to_string().c_str());
        }
    }
    
    void chordNode::freeMessager(int messager) {
        DEBUG_PRINT("Free messager");
        messagerPool[messager].busy = 0;
        messagerPool[messager].closeConnection();
    }
    
    int chordNode::getUsableMessager() {
        DEBUG_PRINT("Getting usable messager.");
        for (int i = 0; i < CHORDNODE_MESSAGER_POOL_SIZE; ++i) {
            if (messagerPool[i].busy == 0) {
                messagerPool[i].busy = 1;
                return i;
            }
        }
        return -1;
    }
    
    void chordNode::sendData(std::ifstream& is, node_t dest_node, std::string key, int size) {
        DEBUG_PRINT("ChordNode sending data");
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageDataInfo(thisNode, dest_node, key, size);
        int newmessager = getUsableMessager();
        if (newmessager == -1) {
            throw ERRORS::chordMessagerNoUsableMessager();
        }
        messagerPool[newmessager].setMode(1);
        messagerPool[newmessager].setRemoteHost(outmsg->getDestHostname());
        messagerPool[newmessager].setRemotePort(outmsg->getDestPortno());
        messagerPool[newmessager].init();
        messagerPool[newmessager].startConnect();
        std::string serialized_msg = outmsg->serialize();
        messagerPool[newmessager].sendMessage(serialized_msg);
        std::string ack = messagerPool[newmessager].readMessage();
        messagerPool[newmessager].sendData(is, size);
        ack = messagerPool[newmessager].readMessage();
        delete outmsg;
        freeMessager(newmessager);
    }
    
    void chordNode::receiveData(int messager, chordMessager::chordMessageBase* inmsg) {
        DEBUG_PRINT("chordNode receiving data");
        std::string fname = inmsg->getKeyParam()[0];
        identifier_t size = inmsg->getIntParam()[0];
        std::ofstream os(datapath + "/" + fname);
        if (!os) {
            throw ERRORS::chordFileCreateFail();
        }
        messagerPool[messager].sendMessage("ack");
        messagerPool[messager].receiveData(os, size);
        os.close();
        messagerPool[messager].sendMessage("ack");
    }
    
    void chordNode::makeRequest(chordMessager::chordMessageBase* outmsg, chordMessager::chordMessageBase*& inmsg) {
        DEBUG_PRINT("Making a request");
        int newmessager = getUsableMessager();
        if (newmessager == -1) {
            throw ERRORS::chordMessagerNoUsableMessager();
        }
        messagerPool[newmessager].setMode(1);
        messagerPool[newmessager].setRemoteHost(outmsg->getDestHostname());
        messagerPool[newmessager].setRemotePort(outmsg->getDestPortno());
        messagerPool[newmessager].init();
        messagerPool[newmessager].startConnect();
        std::string serialized_msg = outmsg->serialize();
        messagerPool[newmessager].sendMessage(serialized_msg);
        //wait for reply
        std::string msg = messagerPool[newmessager].readMessage();
        messagerPool[newmessager].deserializeMessage(msg, inmsg);
        //free messager
        freeMessager(newmessager);
    }
    
    node_t chordNode::getRemoteSuccessor(node_t dest_node) {
        if (dest_node == thisNode) {
            return getSuccessor();
        }
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageGetSuccessor(thisNode, dest_node);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        delete outmsg;
        return ret;
    }
    
    node_t chordNode::getRemotePredecessor(node_t dest_node) {
        if (dest_node == thisNode) {
            return getPredecessor();
        }
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageGetPredecessor(thisNode, dest_node);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        delete outmsg;
        return ret;
    }
    
    void chordNode::updateRemoteFingerTable(node_t dest_node, node_t node_param, identifier_t int_param) {
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageUpdateFingerTable(thisNode, dest_node, node_param, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        delete inmsg;
        delete outmsg;
    }
    
    void chordNode::removeRemoteNode(node_t dest_node, node_t node_param1, node_t node_param2, identifier_t int_param) {
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageRemoveNode(thisNode, dest_node, node_param1, node_param2, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        delete inmsg;
        delete outmsg;
    }
    
    void chordNode::setRemotePredecessor(node_t dest_node, node_t node_param) {
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageSetPredecessor(thisNode, dest_node, node_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        delete inmsg;
        delete outmsg;
    }
    
    node_t chordNode::findRemoteSuccessor(node_t dest_node, identifier_t int_param) {
        if (dest_node == thisNode) {
            return findSuccessor(int_param);
        }
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageFindSuccessor(thisNode, dest_node, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        delete outmsg;
        return ret;
    }
    
    node_t chordNode::findRemoteClosestPrecedingFinger(node_t dest_node, identifier_t int_param) {
        if (dest_node == thisNode) {
            return closestPrecedingFinger(int_param);
        }
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageClosestPrecedingFinger(thisNode, dest_node, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        delete outmsg;
        return ret;
    }
    
    //find id's successor
    node_t chordNode::findSuccessor(identifier_t id) {
        DEBUG_PRINT("Find successor");
        node_t n = getRemoteSuccessor(findPredecessor(id));
        return n;
    }
    
    //find id's predecessor
    node_t chordNode::findPredecessor(identifier_t id) {
        DEBUG_PRINT("Find predecessor");
        node_t node = thisNode;
        while (!inRange(id, node.identifier + 1, getRemoteSuccessor(node).identifier)) {
            node_t n = findRemoteClosestPrecedingFinger(node, id);
            if (n == node) {
                break;
            }
            node = n;
        }
        return node;
    }
    
    //find closest preceding finger
    node_t chordNode::closestPrecedingFinger(identifier_t id) {
        DEBUG_PRINT("Find closestPrecedingFinger");
        for (int i = IDENTIFIER_LEN; i >= 1; --i) {
            if (inRange(finger[i].node.identifier, thisNode.identifier + 1, id - 1)) {
                return finger[i].node;
            }
        }
        return thisNode;
    }
    
    void chordNode::join(node_t existNode) {
        DEBUG_PRINT("Joining the chord network");
        if (existNode.hostname.empty()) {
            //this is the only node in the network
            for (int i = 1; i <= IDENTIFIER_LEN; ++i) {
                finger[i].node = thisNode;
            }
            predecessor = thisNode;
        }else {
            initFingerTable(existNode);
            updateOthers();
            //move keys from the successor that should be placed on this node
            moveSuccessorKeysToLocal();
        }
        initiated = true;
        DEBUG_PRINT("Node successfully joined the network!");
    }
    
    void chordNode::initFingerTable(node_t existNode) {
        DEBUG_PRINT("Init fingertable");
        finger[1].node = findRemoteSuccessor(existNode, finger[1].start);
        node_t cur_successor = getSuccessor();
        predecessor = getRemotePredecessor(cur_successor);
        setRemotePredecessor(cur_successor, thisNode);
        for (int i = 1; i <= IDENTIFIER_LEN - 1; ++i) {
            if (inRange(finger[i + 1].start, thisNode.identifier, finger[i].node.identifier - 1)) {
                finger[i + 1].node = finger[i].node;
            }else {
                finger[i + 1].node = findRemoteSuccessor(existNode, finger[i + 1].start);
                if (!inRange(finger[i + 1].node.identifier, finger[i + 1].start, thisNode.identifier)) {
                    finger[i + 1].node = thisNode;
                }
            }
        }
    }
    
    void chordNode::updateOthers() {
        DEBUG_PRINT("update other chord nodes");
        for (int i = 1; i <= IDENTIFIER_LEN; ++i) {
            identifier_t pos = thisNode.identifier - (identifier_t)pow(2, i - 1) + 1;
            if (pos < 0) {
                pos += (identifier_t)pow(2, IDENTIFIER_LEN);
            }
            node_t p = findPredecessor(pos);
            updateRemoteFingerTable(p, thisNode, i);
        }
    }
    
    void chordNode::updateFingerTable(node_t node, identifier_t i) {
        DEBUG_PRINT("Updating finger table");
        if (node.identifier == thisNode.identifier) {
            return;
        }
        if (inRange(node.identifier, thisNode.identifier + 1, finger[i].node.identifier)) {
            finger[i].node = node;
            updateRemoteFingerTable(predecessor, node, i);
        }
    }
    
    void chordNode::moveSuccessorKeysToLocal() {
        node_t successor = getSuccessor();
        std::vector<std::string> successor_keys = getRemoteStoredKeys(successor);
        for (std::string key : successor_keys) {
            if (inRange(getHashcode(key), predecessor.identifier, thisNode.identifier)) {
                addKeyLocal(key);
                fetchKeyValue(key);
                removeKeyRemote(key, successor);
                removeRemoteDataFromDisk(key, successor);
            }
        }
    }
    
    void chordNode::moveLocalKeysToSuccessor() {
        //move all keys to successor
        node_t successor = getSuccessor();
        for (auto iter = stored_keys.begin(); iter != stored_keys.end(); ++iter) {
            addKeyRemote(iter->first, successor);
        }
        //send all local files to successor
        for (auto iter = stored_keys.begin(); iter != stored_keys.end(); ++iter) {
            std::ifstream is(datapath + iter->first, std::ifstream::binary);
            if (!is) {
                throw ERRORS::chordFileOpenFail();
            }
            is.seekg(0, is.end);
            int size = is.tellg();
            is.seekg(0, is.beg);
            sendData(is, successor, iter->first, size);
            is.close();
        }
        //remove all local stored file data
        for (auto& p : stored_keys) {
            removeLocalDataFromDisk(p.first);
        }
    }
    
    void chordNode::leave() {
        DEBUG_PRINT("chord node is leaving the network");
        if (thisNode == getSuccessor()) {
            return;
        }
        moveLocalKeysToSuccessor();
        node_t cur_successor = getSuccessor();
        setRemotePredecessor(cur_successor, predecessor);
        for (int i = 1; i <= IDENTIFIER_LEN; ++i) {
            node_t p = findPredecessor(thisNode.identifier - (identifier_t)pow(2, i - 1) + 1);
            removeRemoteNode(p, thisNode, getSuccessor(), i);
        }
    }
    
    void chordNode::removeNode(node_t n, identifier_t i, node_t repl) {
        if (finger[i].node == n) {
            finger[i].node = repl;
            node_t p = predecessor;
            removeRemoteNode(p, n, repl, i);
        }
    }
    
    //get node's successor
    node_t chordNode::getSuccessor() {
        return finger[1].node;
    }
    
    node_t chordNode::getPredecessor() {
        return predecessor;
    }
    
    std::string chordNode::getHostname() {
        return thisNode.hostname;
    }
    
    //get node's identifier
    identifier_t chordNode::getIdentifier() {
        return thisNode.identifier;
    }
    
    int chordNode::getPortno() {
        return thisNode.portno;
    }
    
    std::string chordNode::getMachineName() {
        return thisNode.machine_name;
    }
    
    //key storage
    void chordNode::storeKeyValue(std::string key, std::ifstream& is, int size) {
        //first add key to chord node
        addKey(key);
        //send value to that node
        node_t dest_node = getKeyHostNode(key);
        sendData(is, dest_node, key, size);
    }
    
    void chordNode::fetchKeyValue(std::string key) {
        node_t dest_node = getKeyHostNode(key);
        if (dest_node == thisNode) {
            //the key is stored locally
            return;
        }
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageDataRequest(thisNode, dest_node, key);
        int newmessager = getUsableMessager();
        if (newmessager == -1) {
            throw ERRORS::chordMessagerNoUsableMessager();
        }
        messagerPool[newmessager].setMode(1);
        messagerPool[newmessager].setRemoteHost(outmsg->getDestHostname());
        messagerPool[newmessager].setRemotePort(outmsg->getDestPortno());
        messagerPool[newmessager].init();
        messagerPool[newmessager].startConnect();
        std::string serialized_msg = outmsg->serialize();
        messagerPool[newmessager].sendMessage(serialized_msg);
        std::string msg = messagerPool[newmessager].readMessage();
        chordMessager::chordMessageBase* inmsg = nullptr;
        messagerPool[newmessager].deserializeMessage(msg, inmsg);
        int size = inmsg->getIntParam()[0];
        messagerPool[newmessager].sendMessage("ack");
        std::ofstream os(datapath + "/" + key);
        if (!os) {
            throw ERRORS::chordFileCreateFail();
        }
        messagerPool[newmessager].receiveData(os, size);
        messagerPool[newmessager].sendMessage("ack");
        os.close();
        delete outmsg;
        delete inmsg;
        freeMessager(newmessager);
    }
    
    void chordNode::sendRequestData(int messager, std::string key) {
        std::ifstream is(datapath + key);
        if (!is) {
            throw ERRORS::chordFileOpenFail();
        }
        is.seekg(0, is.end);
        int size = is.tellg();
        is.seekg(0, is.beg);
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageDataInfo(node_t(), node_t(), key, size);
        std::string serialized_msg = outmsg->serialize();
        messagerPool[messager].sendMessage(serialized_msg);
        std::string ack = messagerPool[messager].readMessage();
        messagerPool[messager].sendData(is, size);
        ack = messagerPool[messager].readMessage();
        is.close();
        delete outmsg;
    }
    
    void chordNode::addKey(std::string key) {
        node_t dest_node = getKeyHostNode(key);
        if (dest_node == thisNode) {
            addKeyLocal(key);
        }else {
            addKeyRemote(key, dest_node);
        }
    }
    
    void chordNode::addKeyLocal(std::string key) {
        stored_keys[key] = getHashcode(key);
    }
    
    void chordNode::addKeyRemote(std::string key, node_t dest_node) {
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageStoreKey(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        delete inmsg;
        delete outmsg;
    }
    
    void chordNode::removeKey(std::string key) {
        node_t dest_node = getKeyHostNode(key);
        if (dest_node == thisNode) {
            removeKeyLocal(key);
        }else {
            removeKeyRemote(key, dest_node);
        }
    }
    
    void chordNode::removeKeyLocal(std::string key) {
        if (stored_keys.find(key) != stored_keys.end()) {
            stored_keys.erase(key);
        }
    }
    
    void chordNode::removeKeyRemote(std::string key, node_t dest_node) {
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageEraseKey(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        delete inmsg;
        delete outmsg;
    }
    
    bool chordNode::hasKey(std::string key) {
        node_t dest_node = getKeyHostNode(key);
        if (dest_node == thisNode) {
            return hasKeyLocal(key);
        }else {
            return hasKeyRemote(key, dest_node);
        }
    }
    
    bool chordNode::hasKeyLocal(std::string key) {
        return stored_keys.find(key) != stored_keys.end();
    }
    
    bool chordNode::hasKeyRemote(std::string key, node_t dest_node) {
        node_t hostnode = getKeyHostNode(key);
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageHasKey(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        bool ret = inmsg->getIntParam()[0] == 1;
        delete inmsg;
        delete outmsg;
        return ret;
    }
    
    std::vector<std::string> chordNode::getLocalStoredKeys() {
        std::vector<std::string> keys;
        for (auto& p : stored_keys) {
            keys.push_back(p.first);
        }
        return keys;
    }
    
    std::vector<std::string> chordNode::getRemoteStoredKeys(node_t dest_node) {
        chordMessager::chordMessageBase* inmsg = nullptr;
        std::vector<std::string> keys;
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageRetrieveKeys(thisNode, dest_node);
        makeRequest(outmsg, inmsg);
        for (std::string key: inmsg->getKeyParam()) {
            keys.push_back(key);
        }
        delete inmsg;
        delete outmsg;
        return keys;
    }
    
    std::vector<std::string> chordNode::getGlobalStoredKeys() {
        std::vector<std::string> keys = getLocalStoredKeys();
        node_t next_node = getSuccessor();
        while (next_node != thisNode ) {
            std::vector<std::string> tmp_keys = getRemoteStoredKeys(next_node);
            for (std::string key : tmp_keys) {
                keys.push_back(key);
            }
            next_node = getRemoteSuccessor(next_node);
        }
        return keys;
    }
    
    node_t chordNode::getKeyHostNode(std::string key) {
        return findSuccessor(getHashcode(key));
    }
    
    void chordNode::removeLocalDataFromDisk(std::string key) {
        std::string cmd = "rm " + datapath + key;
        system(cmd.c_str());
    }
    
    void chordNode::removeRemoteDataFromDisk(std::string key, node_t dest_node) {
        chordMessager::chordMessageBase* outmsg = new chordMessager::chordMessageRemoveDataFromDisk(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(outmsg, inmsg);
        delete outmsg;
        delete inmsg;
    }
    
    void chordNode::executeChordMessage(chordMessager::chordMessageBase* inmsg, chordMessager::chordMessageBase*& outmsg, int newmessager) {
        DEBUG_PRINT("executeChordMessage");
        int msg_type = inmsg->getType();
        if (msg_type == chordMessager::chordMessageType::messageGetSuccessor) {
            outmsg = new chordMessager::chordMessageNodeInfo(node_t(), node_t(), getSuccessor());
        }else if (msg_type == chordMessager::chordMessageType::messageGetPredecessor) {
            outmsg = new chordMessager::chordMessageNodeInfo(node_t(), node_t(), getPredecessor());
        }else if (msg_type == chordMessager::chordMessageType::messageSetPredecessor) {
            predecessor = inmsg->getNodeParam()[0];
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageClosestPrecedingFinger) {
            outmsg = new chordMessager::chordMessageNodeInfo(node_t(), node_t(), closestPrecedingFinger(inmsg->getIntParam()[0]));
        }else if (msg_type == chordMessager::chordMessageType::messageFindSuccessor) {
            outmsg = new chordMessager::chordMessageNodeInfo(node_t(), node_t(), findSuccessor(inmsg->getIntParam()[0]));
        }else if (msg_type == chordMessager::chordMessageType::messageUpdateFingerTable) {
            updateFingerTable(inmsg->getNodeParam()[0], inmsg->getIntParam()[0]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageRemoveNode) {
            removeNode(inmsg->getNodeParam()[0], inmsg->getIntParam()[0], inmsg->getNodeParam()[1]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageDetectNodeResponse) {
            //notify the service to stop sending detecting node messages.
            if (!gotDetectNodeResponse) {
                gotDetectNodeResponse = true;
                join(inmsg->getNodeParam()[0]);
            }
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageStoreKey) {
            addKeyLocal(inmsg->getKeyParam()[0]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageDataInfo) {
            receiveData(newmessager, inmsg);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageDataRequest) {
            sendRequestData(newmessager, inmsg->getKeyParam()[0]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageRemoveDataFromDisk) {
            removeLocalDataFromDisk(inmsg->getKeyParam()[0]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageStoreKey) {
            addKeyLocal(inmsg->getKeyParam()[0]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageEraseKey) {
            removeKeyLocal(inmsg->getKeyParam()[0]);
            outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
        }else if (msg_type == chordMessager::chordMessageType::messageHasKey) {
            if (hasKeyLocal(inmsg->getKeyParam()[0])) {
                outmsg = new chordMessager::chordMessageExistence(node_t(), node_t(), 1);
            }else {
                outmsg = new chordMessager::chordMessageExistence(node_t(), node_t(), 0);
            }
        }else if (msg_type == chordMessager::chordMessageType::messageRetrieveKeys) {
            outmsg = new chordMessager::chordMessageKeylist(node_t(), node_t(), getLocalStoredKeys());
        }else {
            throw ERRORS::chordMessagerUnknownMessageType();
        }
    }
    
}//end of namespace CHORD