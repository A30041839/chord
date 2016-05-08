//
//  chordNode.h
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordNode_h
#define chordNode_h

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <thread>
#include <chrono>
#include "chordMessager/chordMessager.h"
#include "chordMessager/chordMessage.h"
#include "debug.h"
#include "utils.h"
#include "types.h"
#include "chordRPCClient.cc"

namespace CHORD {

  //finger entry structure
  struct fingerEntry {
    identifier_t start;
    node_t node;
    std::string to_string() {
      char buf[200];
      sprintf(buf, "start:%lld|", start);
      std::string str(buf);
      str.append(node.to_string());
      return str;
    }
  };

  class chordNode {
    public:
      //this node
      node_t thisNode;

      //rpc client
      rpcsenderClient* rpcSender = nullptr;

      //the predecessor of this node
      node_t predecessor;

      //finger table
      fingerEntry finger[IDENTIFIER_LEN + 1];

      //messager pool
      chordMessager::chordMessager messagerPool[CHORDNODE_MESSAGER_POOL_SIZE];

      //data storage path
      std::string datapath;

      //Detect Response status
      bool gotDetectNodeResponse;

      //chordNode initiate status
      bool initiated;

      //stored keys: key->identifier
      std::unordered_map<std::string, identifier_t> stored_keys;

      //releasea messager
      void freeMessager(int);

      ~chordNode();

      chordNode(std::string _hostname, int _portno, std::string machine_name);

      //get the index of a usable messager
      int getUsableMessager();

      //print out the current values of finger table
      void dumpFingerTable();

      //get node's hostname/ip address
      std::string getHostname();

      //get node's identifier
      identifier_t getIdentifier();

      //get node's port number
      int getPortno();

      //get node's machine name
      std::string getMachineName();

      //find id's successor
      node_t findSuccessor(identifier_t id);

      //find id's predecessor
      node_t findPredecessor(identifier_t id);

      //find closest finger preceding id
      node_t closestPrecedingFinger(identifier_t id);

      //get this node's successor
      node_t getSuccessor();

      //get this node's predecessor
      node_t getPredecessor();

      //get remote's predecessor
      node_t getRemotePredecessor(const node_t& dest_node);

      //set remote's predecessor
      void setRemotePredecessor(const node_t& dest_node, const node_t& node_param);

      //get remote's successor
      node_t getRemoteSuccessor(const node_t& dest_node);

      //find id's successor on remote node
      node_t findRemoteSuccessor(const node_t& dest_node, identifier_t int_param);

      //find id's closest preceding finger on remote node
      node_t findRemoteClosestPrecedingFinger(const node_t& dest_node, identifier_t int_param);

      //update remote's finger table with node n
      void updateRemoteFingerTable(const node_t& dest_node, const node_t& node_param, identifier_t int_param);

      //remove node on remote node
      void removeRemoteNode(const node_t& dest_node, const node_t& node_param1, const node_t& node_param2, identifier_t int_param);

      //join the network
      void join(const node_t& existNode);

      //leaves the network, transfer all keys stored locally to successor
      void leave();

      //move all local keys to the successor
      void moveLocalKeysToSuccessor();

      //move keys from the successor that should be placed on this node
      void moveSuccessorKeysToLocal();

      //init finger table
      void initFingerTable(const node_t& existNode);

      //update other chordnode fingertable
      void updateOthers();

      //update other chordnode fingertable
      void updateFingerTable(const node_t& node, identifier_t i);

      //remove a node
      void removeNode(const node_t& n, identifier_t i, const node_t& repl);

      //add a key to chord network
      void addKey(std::string key);

      //add a key to local chord node
      void addKeyLocal(std::string key);

      //add a key to remote chord node
      void addKeyRemote(std::string key, const node_t& dest_node);

      //remove a key from the chord network
      void removeKey(std::string key);

      //remove a key from the local chord network
      void removeKeyLocal(std::string key);

      //remove a key from the remote chord node
      void removeKeyRemote(std::string key, const node_t& dest_node);

      //check if chord network has a key
      bool hasKey(std::string key);

      //check if local chord node has a key
      bool hasKeyLocal(std::string key);

      //check if remote chord node has a key
      bool hasKeyRemote(std::string key, const node_t& dest_node);

      //get all locally stored keys
      std::vector<std::string> getLocalStoredKeys();

      //get all keys stored in the network
      std::vector<std::string> getGlobalStoredKeys();

      //get all keys from a remote node
      std::vector<std::string> getRemoteStoredKeys(const node_t& dest_node);

      //get the successor of a key
      node_t getKeyHostNode(std::string key);

      //store a key-value pair to the network
      void storeKeyValue(std::string key, std::ifstream& is, int size);

      //fetch a file from network
      void fetchKeyValue(std::string key);

      //send a file due to fetch request
      void sendRequestData(int messager, std::string key);

      //send file data
      void sendData(std::ifstream& is, const node_t& dest_node, std::string key, int size);

      //receive file data
      void receiveData(int messager, chordMessager::chordMessageBase* inmsg);

      //remove a data file from local disk
      void removeLocalDataFromDisk(std::string key);

      //remove a data file from remote disk
      void removeRemoteDataFromDisk(std::string key, const node_t& dest_node);

      //detect node response
      void detectNodeResponse(const node_t& node);

      //perform a remote procedure call
      void makeRequest(chordMessager::chordMessageBase*, chordMessager::chordMessageBase*&);

      //execute a particular chord message
      void executeChordMessage(chordMessager::chordMessageBase*, chordMessager::chordMessageBase*&, int messager);
  };
}//namespace CHORD end



#endif /* chordNode_h */
