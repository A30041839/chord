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
    chordNode::chordNode(std::string _hostname, int _portno) {
        DEBUG_PRINT("Creating chordNode");
        thisNode.hostname = _hostname;
        thisNode.identifier = getHashcode(_hostname);
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
        chordMessager::chordMessageBase* inmsg = nullptr;
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
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageGetSuccessor(thisNode, dest_node);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        return ret;
    }
    
    node_t chordNode::getRemotePredecessor(node_t dest_node) {
        if (dest_node == thisNode) {
            return getPredecessor();
        }
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageGetPredecessor(thisNode, dest_node);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        return ret;
    }
    
    void chordNode::updateRemoteFingerTable(node_t dest_node, node_t node_param, identifier_t int_param) {
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageUpdateFingerTable(thisNode, dest_node, node_param, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        delete inmsg;
    }
    
    void chordNode::removeRemoteNode(node_t dest_node, node_t node_param1, node_t node_param2, identifier_t int_param) {
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageRemoveNode(thisNode, dest_node, node_param1, node_param2, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        delete inmsg;
    }
    
    void chordNode::setRemotePredecessor(node_t dest_node, node_t node_param) {
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageSetPredecessor(thisNode, dest_node, node_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        delete inmsg;
    }
    
    node_t chordNode::findRemoteSuccessor(node_t dest_node, identifier_t int_param) {
        if (dest_node == thisNode) {
            return findSuccessor(int_param);
        }
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageFindSuccessor(thisNode, dest_node, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        return ret;
    }
    
    node_t chordNode::findRemoteClosestPrecedingFinger(node_t dest_node, identifier_t int_param) {
        if (dest_node == thisNode) {
            return closestPrecedingFinger(int_param);
        }
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageClosestPrecedingFinger(thisNode, dest_node, int_param);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        node_t ret = inmsg->getNodeParam()[0];
        delete inmsg;
        return ret;
    }
    
    //find id's successor
    node_t chordNode::findSuccessor(identifier_t id) {
        DEBUG_PRINT("Find successor");
        return getRemoteSuccessor(findPredecessor(id));
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
    
    void chordNode::leave() {
        DEBUG_PRINT("chord node is leaving the network");
        if (thisNode == getSuccessor()) {
            return;
        }
        node_t cur_successor = getSuccessor();
        //move all keys to successor
        for (auto iter = stored_keys.begin(); iter != stored_keys.end(); ++iter) {
            addKeyRemote(iter->first, cur_successor);
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
            sendData(is, cur_successor, iter->first, size);
            is.close();
        }
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
    
    
    //key storage
    
    void chordNode::storeKeyValue(std::string key, std::ifstream& is, int size) {
        //first add key to chord node
        addKey(key);
        //send value to that node
        node_t dest_node = getKeyHostNode(key);
        sendData(is, dest_node, key, size);
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
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageStoreKey(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        delete inmsg;
        
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
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageEraseKey(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        delete inmsg;
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
        chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageHasKey(thisNode, dest_node, key);
        chordMessager::chordMessageBase* inmsg = nullptr;
        makeRequest(newmsg, inmsg);
        return inmsg->getIntParam()[0] == 1;
    }
    
    std::vector<std::string> chordNode::getLocalStoredKeys() {
        std::vector<std::string> keys;
        for (auto& p : stored_keys) {
            keys.push_back(p.first);
        }
        return keys;
    }
    
    std::vector<std::string> chordNode::getGlobalStoredKeys() {
        std::vector<std::string> keys = getLocalStoredKeys();
        node_t next_node = getSuccessor();
        chordMessager::chordMessageBase* inmsg = nullptr;
        while (next_node != thisNode ) {
            chordMessager::chordMessageBase* newmsg = new chordMessager::chordMessageRetrieveKeys(thisNode, next_node);
            makeRequest(newmsg, inmsg);
            for (std::string key: inmsg->getKeyParam()) {
                keys.push_back(key);
            }
            delete inmsg;
            next_node = getRemoteSuccessor(next_node);
        }
        return keys;
    }
    
    node_t chordNode::getKeyHostNode(std::string key) {
        return findSuccessor(getHashcode(key));
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
