//
//  chordMessage.cpp
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "chordMessage.hpp"

namespace chordMessager {
    
    //chordMessageBase//
    std::string chordMessageBase::serialize() {
        return "";
    }
    
    node_t chordMessageBase::getSrcNode() {
        return src_node;
    }
    
    std::string chordMessageBase::getSrcHostname() {
        return src_node.hostname;
    }
    
    identifier_t chordMessageBase::getSrcIdentifier() {
        return src_node.identifier;
    }
    
    int chordMessageBase::getSrcPortno() {
        return src_node.portno;
    }
    
    int chordMessageBase::getType() {
        return messageType;
    }
    
    node_t chordMessageBase::getDestNode() {
        return dest_node;
    }
    
    std::string chordMessageBase::getDestHostname() {
        return dest_node.hostname;
    }
    
    int chordMessageBase::getDestPortno() {
        return dest_node.portno;
    }
    
    identifier_t chordMessageBase::getDestIdentifier() {
        return dest_node.identifier;
    }
    
    std::vector<identifier_t> chordMessageBase::getIntParam() {
        return int_params;
    }
    
    std::vector<node_t> chordMessageBase::getNodeParam() {
        return node_params;
    }
    
    std::vector<std::string> chordMessageBase::getKeyParam() {
        return key_params;
    }
    
    //chordMessageAck//
    chordMessageAck::chordMessageAck(node_t _src_node, node_t _dest_node) {
        DEBUG_PRINT("Creating chordMessageAck");
        src_node = _src_node;
        dest_node = _dest_node;
        messageType = chordMessageType::messageAck;
    }
    
    std::string chordMessageAck::serialize() {
        char buf[200];
        sprintf(buf, "type:%d|", messageType);
        return std::string(buf);
    }
    
    //chordMessageNodeInfo//
    chordMessageNodeInfo::chordMessageNodeInfo(node_t _src_node, node_t _dest_node, node_t _node_param) {
        DEBUG_PRINT("Creating chordMessageNodeInfo");
        src_node = _src_node;
        dest_node = _dest_node;
        node_params.push_back(_node_param);
        messageType = chordMessageType::messageNodeInfo;
    }
    
    std::string chordMessageNodeInfo::serialize() {
        DEBUG_PRINT("chordMessageNodeInfo being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|%s", messageType, node_params[0].to_string().c_str());
        return std::string(buf);
    }
    
    
    //chordMessageDataInfo//
    chordMessageDataInfo::chordMessageDataInfo(node_t _src_node, node_t _dest_node, std::string key, identifier_t size) {
        DEBUG_PRINT("Creating chordMessageDataInfo");
        src_node = _src_node;
        dest_node = _dest_node;
        key_params.push_back(key);
        int_params.push_back(size);
        messageType = chordMessageType::messageDataInfo;
    }
    
    std::string chordMessageDataInfo::serialize() {
        DEBUG_PRINT("chordMessageDataInfo being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|key:%s|int_param:%lld|", messageType, key_params[0].c_str(), int_params[0]);
        return std::string(buf);
    }
    
    //chordMessageExistence//
    chordMessageExistence::chordMessageExistence(node_t _src_node, node_t _dest_node, identifier_t _int_param) {
        DEBUG_PRINT("Creating chordMessageExistence");
        src_node = _src_node;
        dest_node = _dest_node;
        int_params.push_back(_int_param);
        messageType = chordMessageType::messageExistence;
    }
    
    std::string chordMessageExistence::serialize() {
        DEBUG_PRINT("chordMessageExistence being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|int_param:%lld|", messageType, int_params[0]);
        return std::string(buf);
    }
    
    //chordMessageStoreKey//
    chordMessageStoreKey::chordMessageStoreKey(node_t _src_node, node_t _dest_node, std::string key) {
        DEBUG_PRINT("Creating chordMessageStoreKey");
        src_node = _src_node;
        dest_node = _dest_node;
        key_params.push_back(key);
        messageType = chordMessageType::messageStoreKey;
    }
    
    std::string chordMessageStoreKey::serialize() {
        DEBUG_PRINT("chordMessageStoreKey being serialized");
        char buf[200];
        sprintf(buf, "type:%d|key:%s|", messageType, key_params[0].c_str());
        return std::string(buf);
    }
    
    //chordMessageEraseKey//
    chordMessageEraseKey::chordMessageEraseKey(node_t _src_node, node_t _dest_node, std::string key) {
        DEBUG_PRINT("Creating chordMessageEraseKey.");
        src_node = _src_node;
        dest_node = _dest_node;
        key_params.push_back(key);
        messageType = chordMessageType::messageEraseKey;
    }
    
    std::string chordMessageEraseKey::serialize() {
        DEBUG_PRINT("chordMessageEraseKey being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|key:%s|", messageType, key_params[0].c_str());
        return std::string(buf);
    }
    
    //chordMessageHasKey//
    chordMessageHasKey::chordMessageHasKey(node_t _src_node, node_t _dest_node, std::string key) {
        DEBUG_PRINT("Creating chordMessageHasKey");
        src_node = _src_node;
        dest_node = _dest_node;
        key_params.push_back(key);
        messageType = chordMessageType::messageHasKey;
    }
    
    std::string chordMessageHasKey::serialize() {
        DEBUG_PRINT("chordMessageHasKey being serialized");
        char buf[200];
        sprintf(buf, "type:%d|key:%s|", messageType, key_params[0].c_str());
        return std::string(buf);
    }
    
    //chordMessageRetrieveKeys//
    chordMessageRetrieveKeys::chordMessageRetrieveKeys(node_t _src_node, node_t _dest_node) {
        DEBUG_PRINT("Creating chordMessageRetrieveKeys");
        src_node = _src_node;
        dest_node = _dest_node;
        messageType = chordMessageType::messageRetrieveKeys;
    }
    
    std::string chordMessageRetrieveKeys::serialize() {
        DEBUG_PRINT("chordMessageRetrieveKeys being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|", messageType);
        return std::string(buf);
    }
    
    //chordMessageKeylist//
    chordMessageKeylist::chordMessageKeylist(node_t _src_node, node_t _dest_node, std::vector<std::string> keys) {
        DEBUG_PRINT("Creating chordMessageKeylist");
        src_node = _src_node;
        dest_node = _dest_node;
        key_params = keys;
        messageType = chordMessageType::messageKeylist;
    }
    
    std::string chordMessageKeylist::serialize() {
        DEBUG_PRINT("chordMessageKeylist being serialized.");
        //AWARE BUF OVERFLOW
        char buf[1000];
        std::string key_str;
        for (int i = 0; i < key_params.size(); ++i) {
            key_str.append(key_params[i] + ",");
        }
        sprintf(buf, "type:%d|keylist:%s|", messageType, key_str.c_str());
        return std::string(buf);
    }
    
    
    //chordMessageDetectNode//
    chordMessageDetectNode::chordMessageDetectNode(node_t _src_node, node_t _dest_node, node_t _node_param)
    {
        DEBUG_PRINT("Creating chordMessageDetectNode");
        messageType = chordMessageType::messageDetectNode;
        src_node = _src_node;
        dest_node = _dest_node;
        node_params.push_back(_node_param);
    }
    
    std::string chordMessageDetectNode::serialize() {
        DEBUG_PRINT("chordMessageDetectNode being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|%s", messageType, node_params[0].to_string().c_str());
        return std::string(buf);
    }
    
    //chordMessageDetectNodeResponse//
    chordMessageDetectNodeResponse::chordMessageDetectNodeResponse(node_t _src_node, node_t _dest_node, node_t _node_param) {
        DEBUG_PRINT("Creating chordMessageDetectNodeResponse");
        messageType = chordMessageType::messageDetectNodeResponse;
        src_node = _src_node;
        dest_node = _dest_node;
        node_params.push_back(_node_param);
    }
    
    std::string chordMessageDetectNodeResponse::serialize() {
        DEBUG_PRINT("chordMessageDetectNodeResponse being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|%s", messageType, node_params[0].to_string().c_str());
        return std::string(buf);
    }
    
    //chordMessageGetSuccessor//
    chordMessageGetSuccessor::chordMessageGetSuccessor(node_t _src_node, node_t _dest_node) {
        DEBUG_PRINT("Creating chordMessageGetSuccessor");
        messageType = chordMessageType::messageGetSuccessor;
        src_node = _src_node;
        dest_node = _dest_node;
    }
    
    std::string chordMessageGetSuccessor::serialize() {
        DEBUG_PRINT("chordMessageGetSuccessor being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|", messageType);
        return std::string(buf);
    }
    
    //chordMessageGetPredecessor//
    chordMessageGetPredecessor::chordMessageGetPredecessor(node_t _src_node, node_t _dest_node) {
        DEBUG_PRINT("Creating chordMessageGetPredecessor");
        messageType = chordMessageType::messageGetPredecessor;
        src_node = _src_node;
        dest_node = _dest_node;
    }
    
    std::string chordMessageGetPredecessor::serialize() {
        DEBUG_PRINT("chordMessageGetPredecessor being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|", messageType);
        return std::string(buf);
    }
    
    //chordMessageSetPredecessor//
    chordMessageSetPredecessor::chordMessageSetPredecessor(node_t _src_node, node_t _dest_node, node_t _node_param) {
        DEBUG_PRINT("Creating chordMessageSetPredecessor");
        messageType = chordMessageType::messageSetPredecessor;
        src_node = _src_node;
        dest_node = _dest_node;
        node_params.push_back(_node_param);
    }

    
    std::string chordMessageSetPredecessor::serialize() {
        DEBUG_PRINT("chordMessageSetPredecessor being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|%s", messageType, node_params[0].to_string().c_str());
        return std::string(buf);
    }
    
    
    //chordMessageFindSuccessor//
    chordMessageFindSuccessor::chordMessageFindSuccessor(node_t _src_node, node_t _dest_node, identifier_t _int_param) {
        DEBUG_PRINT("Creating chordMessageFindSuccessor");
        messageType = chordMessageType::messageFindSuccessor;
        src_node = _src_node;
        dest_node = _dest_node;
        int_params.push_back(_int_param);
    }
    
    std::string chordMessageFindSuccessor::serialize() {
        DEBUG_PRINT("chordMessageFindSuccessor being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|int_param:%lld|", messageType, int_params[0]);
        return std::string(buf);
    }
    
    //chordMessageClosestPrecedingFinger//
    chordMessageClosestPrecedingFinger::chordMessageClosestPrecedingFinger(node_t _src_node, node_t _dest_node, identifier_t _int_param) {
        DEBUG_PRINT("Creating chordMessageClosestPrecedingFinger");
        messageType = chordMessageType::messageClosestPrecedingFinger;
        src_node = _src_node;
        dest_node = _dest_node;
        int_params.push_back(_int_param);
    }
    
    std::string chordMessageClosestPrecedingFinger::serialize() {
        DEBUG_PRINT("chordMessageClosestPrecedingFinger being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|int_param:%lld|", messageType, int_params[0]);
        return std::string(buf);
    }
    
    //chordMessageUpdateFingerTable
    chordMessageUpdateFingerTable::chordMessageUpdateFingerTable(node_t _src_node, node_t _dest_node, node_t _node_param, identifier_t _int_param) {
        DEBUG_PRINT("Creating chordMessageUpdateFingerTable");
        messageType = chordMessageType::messageUpdateFingerTable;
        src_node = _src_node;
        dest_node = _dest_node;
        node_params.push_back(_node_param);
        int_params.push_back(_int_param);
    }
    
    std::string chordMessageUpdateFingerTable::serialize() {
        DEBUG_PRINT("chordMessageUpdateFingerTable being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|%sint_param:%lld|", messageType, node_params[0].to_string().c_str(), int_params[0]);
        return std::string(buf);
    }
    
    //chordMessageRemoveNode
    chordMessageRemoveNode::chordMessageRemoveNode(node_t _src_node, node_t _dest_node, node_t _node_param1, node_t _node_param2, identifier_t _int_param) {
        DEBUG_PRINT("Creating chordMessageRemoveNode");
        messageType = chordMessageType::messageRemoveNode;
        src_node = _src_node;
        dest_node = _dest_node;
        node_params.push_back(_node_param1);
        node_params.push_back(_node_param2);
        int_params.push_back(_int_param);
    }
    
    std::string chordMessageRemoveNode::serialize() {
        DEBUG_PRINT("chordMessageRemoveNode being serialized.");
        char buf[200];
        sprintf(buf, "type:%d|hostname1:%s|identifier1:%lld|portno1:%d|hostname2:%s|identifier2:%lld|portno2:%d|int_param:%lld|", messageType, node_params[0].hostname.c_str(),
                node_params[0].identifier, node_params[0].portno, node_params[1].hostname.c_str(),
                node_params[1].identifier, node_params[1].portno, int_params[0]);
        return std::string(buf);
    }
}