#ifndef CHORD_RPCSERVER
#define CHORD_RPCSERVER
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <grpc++/grpc++.h>
#include "chordRPC.grpc.pb.h"
#include "chordNode.h"
#include "chordRPCClient.cc"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using chordRPC::messageAck;
using chordRPC::messageBoolAck;
using chordRPC::messageNode;
using chordRPC::messageKeyList;
using chordRPC::GetSuccessorRequest;
using chordRPC::GetPredecessorRequest;
using chordRPC::SetPredecessorRequest;
using chordRPC::FindSuccessorRequest;
using chordRPC::ClosestPrecedingFingerRequest;
using chordRPC::UpdateFingerTableRequest;
using chordRPC::RemoveNodeRequest;
using chordRPC::StoreKeyRequest;
using chordRPC::RemoveDataFromDiskRequest;
using chordRPC::RemoveKeyRequest;
using chordRPC::HasKeyRequest;
using chordRPC::RetrieveKeysRequest;
using chordRPC::rpcsender;
using CHORD::chordNode;

class rpcsenderServiceImpl final : public rpcsender::Service {
  Status getPredecessor(ServerContext* context, const GetPredecessorRequest* request, messageNode* reply) override{
    node_t predecessor = thisNode->getPredecessor();
    reply->set_hostname(predecessor.hostname);
    reply->set_id(predecessor.identifier);
    reply->set_portno(predecessor.portno);
    reply->set_machine_name(predecessor.machine_name);
    return Status::OK;
  }

  Status setPredecessor(ServerContext* context, const SetPredecessorRequest* request, messageAck* reply) override{
    node_t predecessor(request->node().hostname(), request->node().id(), request->node().portno(), request->node().machine_name());
    thisNode->predecessor = predecessor;
    return Status::OK;
  } 

  Status getSuccessor(ServerContext* context, const GetSuccessorRequest* request, messageNode* reply) override{
    node_t successor = thisNode->getSuccessor();
    reply->set_hostname(successor.hostname);
    reply->set_id(successor.identifier);
    reply->set_portno(successor.portno);
    reply->set_machine_name(successor.machine_name);
    return Status::OK;		
  }

  Status findSuccessor(ServerContext* context, const FindSuccessorRequest* request, messageNode* reply) override{
    node_t node = thisNode->findSuccessor(request->id());
    reply->set_hostname(node.hostname);
    reply->set_id(node.identifier);
    reply->set_portno(node.portno);
    reply->set_machine_name(node.machine_name);
    return Status::OK;
  }

  Status closestPrecedingFinger(ServerContext* context, const ClosestPrecedingFingerRequest* request, messageNode* reply) override{
    node_t node = thisNode->closestPrecedingFinger(request->id());
    reply->set_hostname(node.hostname);
    reply->set_id(node.identifier);
    reply->set_portno(node.portno);
    reply->set_machine_name(node.machine_name);
    return Status::OK;
  }

  Status updateFingerTable(ServerContext* context, const UpdateFingerTableRequest* request, messageAck* reply) override{
    node_t node;
    identifier_t id = request->id();
    node.hostname = request->node().hostname();
    node.identifier = request->node().id();
    node.portno = request->node().portno();
    node.machine_name = request->node().machine_name();
    thisNode->updateFingerTable(node, id);
    return Status::OK;
  }

  Status removeNode(ServerContext* context, const RemoveNodeRequest* request, messageAck* reply) override{
    node_t node1, node2;
    identifier_t id = request->id();
    node1.hostname = request->node_1().hostname();
    node1.identifier = request->node_1().id();
    node1.portno = request->node_1().portno();
    node1.machine_name = request->node_1().machine_name();

    node2.hostname = request->node_2().hostname();
    node2.identifier = request->node_2().id();
    node2.portno = request->node_2().portno();
    node2.machine_name = request->node_2().machine_name();
    thisNode->removeNode(node1, id, node2);
    return Status::OK;
  }

  Status storeKey(ServerContext* context, const StoreKeyRequest* request, messageAck* reply) override{
    std::string key = request->key();
    thisNode->addKeyLocal(key);
    return Status::OK;
  }

  Status removeDataFromDisk(ServerContext* context, const RemoveDataFromDiskRequest* request, messageAck* reply) override{
    std::string key = request->key();
    thisNode->removeLocalDataFromDisk(key);
    return Status::OK;
  }

  Status removeKey(ServerContext* context, const RemoveKeyRequest* request, messageAck* reply) override{
    std::string key = request->key();
    thisNode->removeKeyLocal(key);
    return Status::OK;
  }

  Status hasKey(ServerContext* context, const HasKeyRequest* request, messageBoolAck* reply) override{
    std::string key = request->key();
    reply->set_value(thisNode->hasKeyLocal(key));
    return Status::OK;
  }

  Status retrieveKeys(ServerContext* context, const RetrieveKeysRequest* request, messageKeyList* reply) override{
    std::vector<std::string> keys = thisNode->getLocalStoredKeys();
    std::string skeys;
    for (int i = 0; i < (int)keys.size(); ++i) {
      skeys.append(keys[i]);
      skeys.push_back(';');
    }
    reply->set_key_list(skeys);
    return Status::OK;
  }

  public:
  chordNode* thisNode = nullptr;

  void bindNode(chordNode* node){
    thisNode = node;
  }
};
#endif
