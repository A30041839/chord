#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "chord.grpc.pb.h"
#include "../types.h"

using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using chord::m_node_t;
using chord::m_void;
using chord::m_int;
using chord::m_node_t_int;
using chord::m_node_t_node_t_int;
using chord::Messager;
class MessagerClient {
 public:
  MessagerClient(std::shared_ptr<Channel> channel)
      : stub_(Messager::NewStub(channel)) {}
   node_t getPredecessor() {
    // Data we are sending to the server.
    m_void request;
    // Container for the data we expect from the server.
    m_node_t reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->getPredecessor(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      node_t node(reply.hostname(), reply.id(), reply.portno(), reply.machine_name());
      return node;
    } else {
      cerr << "RPC failed";
      return NULL;
    }
  }
 
  // Assambles the client's payload, sends it and presents the response back
  // from the server.
  void setPredecessor(const node_t node) {
	   
    m_node_t request;
    m_void reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    request.set_hostname(node.hostname);
    request.set_id(node.identifier);
    request.set_portno(node.portno);
    request.set_machine_name(node.machine_name);
    
    // The actual RPC.
    Status status = stub_->setPredecessor(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return ;
    } else {
      cerr << "RPC failed";
      return ;
    }
  }

  node_t getSuccessor() {
    // Data we are sending to the server.
    m_void request;
    // Container for the data we expect from the server.
    m_node_t reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->getSuccessor(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      node_t node(reply.hostname(), reply.id(), reply.portno(), reply.machine_name());
      return node;
    } else {
      cerr << "RPC failed";
      return NULL;
    }
  }

  node_t findSuccessor(int id) {
    // Data we are sending to the server.
    m_int request;
    // Container for the data we expect from the server.
    m_node_t reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    request.set_id(id);
    // The actual RPC.
    Status status = stub_->findSuccessor(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      node_t node(reply.hostname(), reply.id(), reply.portno(), reply.machine_name());
      return node;
    } else {
      cerr << "RPC failed";
      return NULL;
    }
  }

  node_t findClosestPrecedingFinger(int id) {
    // Data we are sending to the server.
    m_int request;
    // Container for the data we expect from the server.
    m_node_t reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    request.set_id(id);
    // The actual RPC.
    Status status = stub_->findClosestPrecedingFinger(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      node_t node(reply.hostname(), reply.id(), reply.portno(), reply.machine_name());
      return node;
    } else {
      cerr << "RPC failed";
      return NULL;
    }
  }

  void updateFingerTable(node_t node, int id) {
    // Data we are sending to the server.
    m_node_t_int request;
    m_node_t m_node;
    // Container for the data we expect from the server.
    m_void reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    m_node.set_hostname(node.hostname);
    m_node.set_id(node.identifier);
    m_node.set_portno(node.portno);
    m_node.set_machine_name(node.machine_name);
     
    request.set_node(m_node);
    reqeust.set_id(id);
    // The actual RPC.
    Status status = stub_->updateFingerTable(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return ;
    } else {
      cerr << "RPC failed";
      return ;
    }
  }
  void removeNode(node_t node, node_t node_repl, int id) {
    // Data we are sending to the server.
    m_node_t_node_t_int request;
    m_node_t m_node, m_node_repl;
    // Container for the data we expect from the server.
    m_void reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    m_node.set_hostname(node.hostname);
    m_node.set_id(node.identifier);
    m_node.set_portno(node.portno);
    m_node.set_machine_name(node.machine_name);

    m_node_repl.set_hostname(node_repl.hostname);
    m_node_repl.set_id(node_repl.identifier);
    m_node_repl.set_portno(node_repl.portno);
    m_node_repl.set_machine_name(node_repl.machine_name);
     
    request.set_node_1(m_node);
    request.set_node_2(m_node_repl);
    reqeust.set_id(id);
    // The actual RPC.
    Status status = stub_->updateFingerTable(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return ;
    } else {
      cerr << "RPC failed";
      return ;
    }
  }
 
 private:
  std::unique_ptr<Messager::Stub> stub_;
};

// deprecated, new a connection in chordNode instead
// connect to a remote node, return the connection
MessagerClient connect(const node_t remote_node){
  string hostname = remote_node.hostname;
  int portno = remote_node.portno;

  // concatenate hostname:portno
  stringstream sstm;
  sstm << hostname << ":" << portno;
  MessagerClient messagerClient(grpc::CreateChannel(
      sstm.str(), grpc::InsecureChannelCredentials()));
  return messagerClient; 
} 

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  node_t node("localhost", 10, 50000, "machine_name");
  MessagerClient client = connect(node);
  node_t reply = client.getPredecessor();
  std::cout << "client received: " << reply.to_string() << std::endl;

  return 0;
}
