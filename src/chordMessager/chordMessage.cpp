//
//  chordMessage.cpp
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "chordMessage.h"

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

  int chordMessageBase::getSrcDispatcherPortno() {
    return src_node.portno_disp;
  }

  std::string chordMessageBase::getSrcMachineName() {
    return src_node.machine_name;
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

  int chordMessageBase::getDestDispatcherPortno() {
    return dest_node.portno_disp;
  }

  identifier_t chordMessageBase::getDestIdentifier() {
    return dest_node.identifier;
  }

  std::string chordMessageBase::getDestMachineName() {
    return dest_node.machine_name;
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

  chordMessageBase::~chordMessageBase() {}

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
    sprintf(buf, "type:%d|key:%s|int_param:%llu|", messageType, key_params[0].c_str(), int_params[0]);
    return std::string(buf);
  }

  //chordMessageDataRequest//
  chordMessageDataRequest::chordMessageDataRequest(node_t _src_node, node_t _dest_node, std::string key) {
    DEBUG_PRINT("Creating chordMessageDataRequest");
    src_node = _src_node;
    dest_node = _dest_node;
    key_params.push_back(key);
    messageType = chordMessageType::messageDataRequest;
  }

  std::string chordMessageDataRequest::serialize() {
    DEBUG_PRINT("chordMessageDataRequest being serialized.");
    char buf[200];
    sprintf(buf, "type:%d|key:%s|", messageType, key_params[0].c_str());
    return std::string(buf);
  }
}
