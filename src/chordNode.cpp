//
//  chordNode.cpp
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "chordNode.h"

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

  void chordNode::sendData(std::ifstream& is, const node_t& dest_node, std::string key, int size) {
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

  node_t chordNode::getRemoteSuccessor(const node_t& dest_node) {
    if (thisNode == dest_node) {
      return getSuccessor();
    }
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    node_t ret = rpcSender->getSuccessor();
    delete rpcSender;
    rpcSender = nullptr;
    return ret;
  }

  node_t chordNode::getRemotePredecessor(const node_t& dest_node) {
    if (thisNode == dest_node) {
      return getPredecessor();
    }
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    node_t ret = rpcSender->getPredecessor();
    delete rpcSender;
    rpcSender = nullptr;
    return ret;
  }

  void chordNode::updateRemoteFingerTable(const node_t& dest_node, const node_t& node_param, identifier_t int_param) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    rpcSender->updateFingerTable(node_param, int_param);
    delete rpcSender;
    rpcSender = nullptr;
  }

  void chordNode::removeRemoteNode(const node_t& dest_node, const node_t& node_param1, const node_t& node_param2, identifier_t int_param) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    rpcSender->removeNode(node_param1, node_param2, int_param);
    delete rpcSender;
    rpcSender = nullptr;
  }

  void chordNode::setRemotePredecessor(const node_t& dest_node, const node_t& node_param) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    rpcSender->setPredecessor(node_param);
    delete rpcSender;
    rpcSender = nullptr;
  }

  node_t chordNode::findRemoteSuccessor(const node_t& dest_node, identifier_t int_param) {
    if (thisNode == dest_node) {
      return findSuccessor(int_param);
    }
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));

    node_t ret = rpcSender->findSuccessor(int_param);
    delete rpcSender;
    rpcSender = nullptr;
    return ret;
  }

  node_t chordNode::findRemoteClosestPrecedingFinger(const node_t& dest_node, identifier_t int_param) {
    if (thisNode == dest_node) {
      return closestPrecedingFinger(int_param);
    }
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));

    node_t ret = rpcSender->closestPrecedingFinger(int_param);
    delete rpcSender;
    rpcSender = nullptr;
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

  void chordNode::join(const node_t& existNode) {
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

  void chordNode::initFingerTable(const node_t& existNode) {
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

  void chordNode::updateFingerTable(const node_t& node, identifier_t i) {
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

  void chordNode::removeNode(const node_t& n, identifier_t i, const node_t& repl) {
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
    if (thisNode == dest_node) {
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
    if (thisNode == dest_node) {
      addKeyLocal(key);
    }else {
      addKeyRemote(key, dest_node);
    }
  }

  void chordNode::addKeyLocal(std::string key) {
    stored_keys[key] = getHashcode(key);
  }

  void chordNode::addKeyRemote(std::string key, const node_t& dest_node) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    rpcSender->storeKey(key);
    delete rpcSender;
    rpcSender = nullptr;
  }

  void chordNode::removeKey(std::string key) {
    node_t dest_node = getKeyHostNode(key);
    if (thisNode == dest_node) {
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

  void chordNode::removeKeyRemote(std::string key, const node_t& dest_node) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    rpcSender->removeKey(key);
    delete rpcSender;
    rpcSender = nullptr;
  }

  bool chordNode::hasKey(std::string key) {
    node_t dest_node = getKeyHostNode(key);
    if (thisNode == dest_node) {
      return hasKeyLocal(key);
    }else {
      return hasKeyRemote(key, dest_node);
    }
  }

  bool chordNode::hasKeyLocal(std::string key) {
    return stored_keys.find(key) != stored_keys.end();
  }

  bool chordNode::hasKeyRemote(std::string key, const node_t& dest_node) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    bool ret = rpcSender->hasKey(key);
    delete rpcSender;
    rpcSender = nullptr;
    return ret;
  }

  std::vector<std::string> chordNode::getLocalStoredKeys() {
    std::vector<std::string> keys;
    for (auto& p : stored_keys) {
      keys.push_back(p.first);
    }
    return keys;
  }

  std::vector<std::string> chordNode::getRemoteStoredKeys(const node_t& dest_node) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));
    std::string s_keys = rpcSender->retrieveKeys();
    std::vector<std::string> keys = splitStr(s_keys, ':');
    delete rpcSender;
    rpcSender = nullptr;
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

  void chordNode::removeRemoteDataFromDisk(std::string key, const node_t& dest_node) {
    std::string addr = dest_node.hostname + ":" + std::to_string(dest_node.portno);
    rpcSender = new rpcsenderClient(grpc::CreateChannel(
          addr, grpc::InsecureChannelCredentials()));

    rpcSender->removeDataFromDisk(key);
    delete rpcSender;
    rpcSender = nullptr;
  }

  void chordNode::detectNodeResponse(const node_t& node) {
    //notify the service to stop sending detecting node messages.
    if (!gotDetectNodeResponse) {
      gotDetectNodeResponse = true;
      join(node);
    }
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

  void chordNode::executeChordMessage(chordMessager::chordMessageBase* inmsg, chordMessager::chordMessageBase*& outmsg, int newmessager) {
    DEBUG_PRINT("executeChordMessage");
    int msg_type = inmsg->getType();
    if (msg_type == chordMessager::chordMessageType::messageDataInfo) {
      receiveData(newmessager, inmsg);
      outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
    }else if (msg_type == chordMessager::chordMessageType::messageDataRequest) {
      sendRequestData(newmessager, inmsg->getKeyParam()[0]);
      outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
    }else if (msg_type == chordMessager::chordMessageType::messageDetectNodeResponse) {
      detectNodeResponse(inmsg->getNodeParam()[0]);
      outmsg = new chordMessager::chordMessageAck(node_t(), node_t());
    }else {
      throw ERRORS::chordMessagerUnknownMessageType();
    }
  }
}//end of namespace CHORD
