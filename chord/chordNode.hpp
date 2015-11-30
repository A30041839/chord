//
//  chordNode.hpp
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordNode_hpp
#define chordNode_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include "chordMessager/chordMessager.hpp"
#include "chordMessager/chordMessage.hpp"
#include "debug.h"
#include "utils.h"
#include "types.h"

namespace CHORD {
    
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
        node_t predecessor;
        //this node's finger table
        fingerEntry finger[IDENTIFIER_LEN + 1];
        
        //messager pool
        chordMessager::chordMessager messagerPool[CHORDNODE_MESSAGER_POOL_SIZE];
        
        //data storage path
        std::string datapath;
        
        void freeMessager(int);
        
        //Detect Response status
        bool gotDetectNodeResponse;
        
        //chordNode initiate status
        bool initiated;
        
        //stored keys
        std::unordered_map<std::string, identifier_t> stored_keys;
        
        ~chordNode();
        
        chordNode(std::string _hostname, int _portno);
        
        int getUsableMessager();
        
        void dumpFingerTable();
        
        void makeRequest(chordMessager::chordMessageBase*, chordMessager::chordMessageBase*&);
        
        //get node's hostname
        std::string getHostname();
        
        //get node's identifier
        identifier_t getIdentifier();
        
        //get node's port number
        int getPortno();
        
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
        node_t getRemotePredecessor(node_t dest_node);
        
        //set remote's predecessor
        void setRemotePredecessor(node_t dest_node, node_t node_param);
        
        //get remote's successor
        node_t getRemoteSuccessor(node_t dest_node);
        
        //find id's successor on remote
        node_t findRemoteSuccessor(node_t dest_node, identifier_t int_param);
        
        //get remote's closest preceding finger of id
        node_t findRemoteClosestPrecedingFinger(node_t dest_node, identifier_t int_param);
        
        //update remote's finger table with node n
        void updateRemoteFingerTable(node_t dest_node, node_t node_param, identifier_t int_param);
        
        //remove node on remote
        void removeRemoteNode(node_t dest_node, node_t node_param1, node_t node_param2, identifier_t int_param);
        
        //join the network
        void join(node_t existNode);
        
        //init finger table
        void initFingerTable(node_t existNode);
        
        void updateOthers();
        
        void updateFingerTable(node_t node, identifier_t i);
        
        void leave();
        
        void removeNode(node_t n, identifier_t i, node_t repl);
        
        void addKey(std::string key);
        
        void addKeyLocal(std::string key);
        
        void addKeyRemote(std::string key, node_t dest_node);
        
        void removeKey(std::string key);
        
        void removeKeyLocal(std::string key);
        
        void removeKeyRemote(std::string key, node_t dest_node);
        
        bool hasKey(std::string key);
        
        bool hasKeyLocal(std::string key);
        
        bool hasKeyRemote(std::string key, node_t dest_node);
        
        std::vector<std::string> getLocalStoredKeys();
        
        std::vector<std::string> getGlobalStoredKeys();
        
        node_t getKeyHostNode(std::string key);
        
        void storeKeyValue(std::string key, std::ifstream& is, int size);
        
        void sendData(std::ifstream& is, node_t dest_node, std::string key, int size);
        
        void receiveData(int messager, chordMessager::chordMessageBase* inmsg);
        
        void executeChordMessage(chordMessager::chordMessageBase*, chordMessager::chordMessageBase*&, int messager);
    };
}//namespace CHORD end



#endif /* chordNode_hpp */
