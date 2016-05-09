//
//  chordMessage.h
//  chord
//
//  Created by Haoliang on 11/25/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordMessage_h
#define chordMessage_h

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <vector>
#include "../debug.h"
#include "../types.h"

namespace chordMessager {

  enum chordMessageType {
    messageDetectNode,
    messageDetectNodeResponse,
    messageDataInfo,
    messageDataRequest,
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
      virtual int getSrcDispatcherPortno();
      virtual std::string getSrcMachineName();

      virtual node_t getDestNode();
      virtual std::string getDestHostname();
      virtual int getDestDispatcherPortno();
      virtual identifier_t getDestIdentifier();
      virtual std::string getDestMachineName();

      virtual std::vector<identifier_t> getIntParam();
      virtual std::vector<node_t> getNodeParam();
      virtual std::vector<std::string> getKeyParam();
      virtual ~chordMessageBase();
  };

  class chordMessageAck : public chordMessageBase {
    public:
      chordMessageAck(node_t _src_node, node_t _dest_node);
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
}

#endif /* chordMessage_h */
