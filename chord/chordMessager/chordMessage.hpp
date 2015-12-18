//
//  chordMessage.hpp
//  chord
//
//  Created by Haoliang on 11/25/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordMessage_hpp
#define chordMessage_hpp

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <vector>
#include "debug.h"
#include "types.h"

namespace chordMessager {
    
    enum chordMessageType {
        messageNodeInfo = 0,
        messageGetSuccessor,
        messageGetPredecessor,
        messageSetPredecessor,
        messageClosestPrecedingFinger,
        messageFindSuccessor,
        messageUpdateFingerTable,
        messageRemoveNode,
        messageDetectNode,
        messageDetectNodeResponse,
        messageStoreKey,
        messageEraseKey,
        messageHasKey,
        messageExistence,
        messageRetrieveKeys,
        messageKeylist,
        messageDataInfo,
        messageDataRequest,
        messageRemoveDataFromDisk,
        messageAck,
    };
    
    class chordMessageBase {
    public:
        //message receiver
        node_t dest_node;
        
        //message sender
        node_t src_node;
        
        //message type
        chordMessageType messageType;
        
        //node params
        std::vector<node_t> node_params;
        
        //int params
        std::vector<identifier_t> int_params;
        
        //key params
        std::vector<std::string> key_params;
        
        virtual std::string serialize();
        virtual int getType();
        
        virtual node_t getSrcNode();
        virtual std::string getSrcHostname();
        virtual identifier_t getSrcIdentifier();
        virtual int getSrcPortno();
        virtual std::string getSrcMachineName();
        
        virtual node_t getDestNode();
        virtual std::string getDestHostname();
        virtual int getDestPortno();
        virtual identifier_t getDestIdentifier();
        virtual std::string getDestMachineName();
        
        virtual std::vector<identifier_t> getIntParam();
        virtual std::vector<node_t> getNodeParam();
        virtual std::vector<std::string> getKeyParam();
    };
    
    class chordMessageAck : public chordMessageBase {
    public:
        chordMessageAck(node_t _src_node, node_t _dest_node);
        std::string serialize();
    };
    
    class chordMessageNodeInfo : public chordMessageBase {
    public:
        chordMessageNodeInfo(node_t _src_node, node_t _dest_node, node_t _node_param);
        std::string serialize();
    };
    
    class chordMessageDataInfo : public chordMessageBase {
    public:
        chordMessageDataInfo(node_t _src_node, node_t _dest_node, std::string key, identifier_t size);
        std::string serialize();
    };
    
    class chordMessageDataRequest : public chordMessageBase {
    public:
        chordMessageDataRequest(node_t _src_node, node_t _dest_node, std::string key);
        std::string serialize();
    };
    
    class chordMessageRemoveDataFromDisk : public chordMessageBase {
    public:
        chordMessageRemoveDataFromDisk(node_t _src_node, node_t _dest_node, std::string key);
        std::string serialize();
    };
    
    class chordMessageRetrieveKeys : public chordMessageBase {
    public:
        chordMessageRetrieveKeys(node_t _src_node, node_t _dest_node);
        std::string serialize();
    };
    
    class chordMessageKeylist : public chordMessageBase {
    public:
        chordMessageKeylist(node_t _src_node, node_t _dest_node, std::vector<std::string> keys);
        std::string serialize();
    };
    
    class chordMessageExistence : public chordMessageBase {
    public:
        chordMessageExistence(node_t _src_node, node_t _dest_node, identifier_t _int_param);
        std::string serialize();
    };
    
    class chordMessageStoreKey : public chordMessageBase {
    public:
        chordMessageStoreKey(node_t _src_node, node_t _dest_node, std::string key);
        std::string serialize();
    };
    
    class chordMessageEraseKey : public chordMessageBase {
    public:
        chordMessageEraseKey(node_t _src_node, node_t _dest_node, std::string key);
        std::string serialize();
    };
    
    class chordMessageHasKey : public chordMessageBase {
    public:
        chordMessageHasKey(node_t _src_node, node_t _dest_node, std::string key);
        std::string serialize();
    };
    
    class chordMessageDetectNode : public chordMessageBase {
    public:
        chordMessageDetectNode(node_t _src_node, node_t _dest_node, node_t _node_param);
        std::string serialize();
    };
    
    class chordMessageDetectNodeResponse : public chordMessageBase {
    public:
        chordMessageDetectNodeResponse(node_t _src_node, node_t _dest_node, node_t _node_param);
        std::string serialize();
    };
    
    //get remote's successor
    class chordMessageGetSuccessor : public chordMessageBase {
    public:
        chordMessageGetSuccessor(node_t _src_node, node_t _dest_node);
        std::string serialize();
    };
    
    //get remote's predecessor
    class chordMessageGetPredecessor : public chordMessageBase {
    public:
        chordMessageGetPredecessor(node_t _src_node, node_t _dest_node);
        std::string serialize();
    };
    
    //set remote's predecessor
    class chordMessageSetPredecessor : public chordMessageBase {
    public:
        chordMessageSetPredecessor(node_t _src_node, node_t _dest_node, node_t _node_param);
        std::string serialize();
    };
    
    //find id's successor on remote
    class chordMessageFindSuccessor : public chordMessageBase {
    public:
        chordMessageFindSuccessor(node_t _src_node, node_t _dest_node, identifier_t _int_param);
        std::string serialize();
    };
    
    class chordMessageClosestPrecedingFinger : public chordMessageBase {
    public:
        chordMessageClosestPrecedingFinger(node_t _src_node, node_t _dest_node, identifier_t _int_param);
        std::string serialize();
    };
    
    class chordMessageUpdateFingerTable : public chordMessageBase {
    public:
        chordMessageUpdateFingerTable(node_t _src_node, node_t _dest_node, node_t _node_param, identifier_t _int_param);
        std::string serialize();
    };

    class chordMessageRemoveNode : public chordMessageBase {
    public:
        chordMessageRemoveNode(node_t _src_node, node_t _dest_node, node_t _node_param1, node_t _node_param2, identifier_t _int_param);
        std::string serialize();
    };
}

#endif /* chordMessage_hpp */
