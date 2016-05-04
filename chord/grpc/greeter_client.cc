#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "chord.grpc.pb.h"
#include "types.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using chord::m_note_t;
using chord::m_void;
using chord::m_int;
using chord::m_node_t_int
using chord::m_node_t_node_t_int
using chord::Messager;
using namespace std;
class MessagerClient {
 public:
  MessagerClient(std::shared_ptr<Channel> channel)
      : stub_(Messager::NewStub(channel)) {}

  // Assambles the client's payload, sends it and presents the response back
  // from the server.
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
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

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
