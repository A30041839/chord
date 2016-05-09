#ifndef CHORD_RPCCLIENT
#define CHORD_RPCCLIENT

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <sstream>
#include "chordRPC.grpc.pb.h"
#include "types.h"
#include "errors.h"

using grpc::Channel;
using grpc::ClientContext;
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

class rpcsenderClient {
  public:
    rpcsenderClient(std::shared_ptr<Channel> channel)
      : stub_(rpcsender::NewStub(channel)) {}
    node_t getPredecessor() {
      GetPredecessorRequest request;
      // Container for the data we expect from the server.
      messageNode reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      // The actual RPC.
      Status status = stub_->getPredecessor(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return node_t(reply.hostname(), reply.id(), reply.portno_disp(), reply.portno_rpc(), reply.machine_name());
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    // Assambles the client's payload, sends it and presents the response back
    // from the server.
    void setPredecessor(const node_t& node) {
      SetPredecessorRequest request;
      messageAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      request.mutable_node()->set_hostname(node.hostname);
      request.mutable_node()->set_id(node.identifier);
      request.mutable_node()->set_portno_disp(node.portno_disp);
      request.mutable_node()->set_portno_rpc(node.portno_rpc);
      request.mutable_node()->set_machine_name(node.machine_name);

      // The actual RPC.
      Status status = stub_->setPredecessor(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return;
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    node_t getSuccessor() {
      // Data we are sending to the server.
      GetSuccessorRequest request;
      // Container for the data we expect from the server.
      messageNode reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      // The actual RPC.
      Status status = stub_->getSuccessor(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return node_t(reply.hostname(), reply.id(), reply.portno_disp(), reply.portno_rpc(), reply.machine_name());
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    node_t findSuccessor(identifier_t id) {
      // Data we are sending to the server.
      FindSuccessorRequest request;
      // Container for the data we expect from the server.
      messageNode reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;
      request.set_id(id);
      // The actual RPC.
      Status status = stub_->findSuccessor(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return node_t(reply.hostname(), reply.id(), reply.portno_disp(), reply.portno_rpc(), reply.machine_name());
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    node_t closestPrecedingFinger(identifier_t id) {
      // Data we are sending to the server.
      ClosestPrecedingFingerRequest request;
      // Container for the data we expect from the server.
      messageNode reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;
      request.set_id(id);
      // The actual RPC.
      Status status = stub_->closestPrecedingFinger(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return node_t(reply.hostname(), reply.id(), reply.portno_disp(), reply.portno_rpc(), reply.machine_name());
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    void updateFingerTable(const node_t& node, identifier_t id) {
      // Data we are sending to the server.
      UpdateFingerTableRequest request;
      // Container for the data we expect from the server.
      messageAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      request.mutable_node()->set_hostname(node.hostname);
      request.mutable_node()->set_id(node.identifier);
      request.mutable_node()->set_portno_disp(node.portno_disp);
      request.mutable_node()->set_portno_rpc(node.portno_rpc);
      request.mutable_node()->set_machine_name(node.machine_name);
      request.set_id(id);

      // The actual RPC.
      Status status = stub_->updateFingerTable(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return ;
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    void removeNode(const node_t& node, const node_t& node_repl, identifier_t id) {
      // Data we are sending to the server.
      RemoveNodeRequest request;
      // Container for the data we expect from the server.
      messageAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;
      request.mutable_node_1()->set_hostname(node.hostname);
      request.mutable_node_1()->set_id(node.identifier);
      request.mutable_node_1()->set_portno_disp(node.portno_disp);
      request.mutable_node_1()->set_portno_rpc(node.portno_rpc);
      request.mutable_node_1()->set_machine_name(node.machine_name);

      request.mutable_node_2()->set_hostname(node_repl.hostname);
      request.mutable_node_2()->set_id(node_repl.identifier);
      request.mutable_node_2()->set_portno_disp(node_repl.portno_disp);
      request.mutable_node_2()->set_portno_rpc(node_repl.portno_rpc);
      request.mutable_node_2()->set_machine_name(node_repl.machine_name);

      request.set_id(id);

      // The actual RPC.
      Status status = stub_->removeNode(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return ;
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    void storeKey(std::string key) {
      // Data we are sending to the server.
      StoreKeyRequest request;
      // Container for the data we expect from the server.
      messageAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      request.set_key(key);
      // The actual RPC.
      Status status = stub_->storeKey(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return ;
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    void removeDataFromDisk(std::string key) {
      // Data we are sending to the server.
      RemoveDataFromDiskRequest request;
      // Container for the data we expect from the server.
      messageAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      request.set_key(key);
      // The actual RPC.
      Status status = stub_->removeDataFromDisk(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return ;
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    void removeKey(std::string key) {
      // Data we are sending to the server.
      RemoveKeyRequest request;
      // Container for the data we expect from the server.
      messageAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      request.set_key(key);
      // The actual RPC.
      Status status = stub_->removeKey(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return ;
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    bool hasKey(std::string key) {
      // Data we are sending to the server.
      HasKeyRequest request;
      // Container for the data we expect from the server.
      messageBoolAck reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      request.set_key(key);
      // The actual RPC.
      Status status = stub_->hasKey(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        if (reply.value()) {
          return true;
        }else {
          return false;
        }
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

    std::string retrieveKeys() {
      // Data we are sending to the server.
      RetrieveKeysRequest request;
      // Container for the data we expect from the server.
      messageKeyList reply;

      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;

      // The actual RPC.
      Status status = stub_->retrieveKeys(&context, request, &reply);

      // Act upon its status.
      if (status.ok()) {
        return reply.key_list();
      } else {
        throw ERRORS::chordRPCFail();
      }
    }

  private:
    std::unique_ptr<rpcsender::Stub> stub_;
};
#endif
