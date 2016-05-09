//
//  chordService.cpp
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "chordService.h"

namespace CHORD {
  //static member initialization must be put in cpp file!
  chordService* chordService::serviceInstance = nullptr;
  chordMessageDispatcher* chordService::serviceDispatcher = nullptr;
  chordNode* chordService::serviceChordNode = nullptr;
  std::thread* chordService::serviceDispatcherThread = nullptr;
  std::thread* chordService::serviceDetectNodesResponseThread = nullptr;
  std::thread* chordService::serviceRPCServerThread = nullptr;
  rpcsenderServiceImpl* chordService::rpc_service = nullptr;
  bool chordService::initialized = false;
  bool chordService::rpcserverInitialized = false;

  chordService::chordService() {
    DEBUG_PRINT("Creating Chord service.");
  }

  chordService* chordService::createService(std::string hostname, int portno_disp, int portno_rpc, std::string machine_name) {
    if (serviceInstance == nullptr) {
      //initiate service here
      serviceInstance = new chordService();
      serviceChordNode = new chordNode(hostname, portno_disp, portno_rpc, machine_name);
      //bind chordNode to dispatcher
      serviceDispatcher = new chordMessageDispatcher(serviceChordNode);
      serviceDispatcherThread = new std::thread(startDispatcher);
      rpc_service = new rpcsenderServiceImpl();
      rpc_service->bindNode(serviceChordNode);
      serviceRPCServerThread = new std::thread(startRPCServer, hostname + ":" + std::to_string(portno_rpc));
      while (!serviceDispatcher->isListenning() or !rpcserverInitialized) {
      }
      detectNodes();
      while (!serviceChordNode->initiated) {
      }
      //start detect node response process after finger table is initialized
      serviceDetectNodesResponseThread = new std::thread(detectNodesResponse);
      initialized = true;
    }
    return serviceInstance;
  }

  void chordService::startDispatcher() {
    serviceDispatcher->startListen();
  }

  void chordService::startRPCServer(std::string server_address) {
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "rpc_service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* rpc_service.
    builder.RegisterService(rpc_service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::string info =  "RPC Server listening on " + server_address;
    DEBUG_PRINT(info.c_str());
    rpcserverInitialized = true;
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
  }

  chordService* chordService::getServiceInstance() {
    if (serviceInstance == nullptr) {
      throw ERRORS::chordServiceNotInitiated();
    }
    return serviceInstance;
  }

  void chordService::detectNodes() {
    DEBUG_PRINT("chordService is detecting existing nodes.");
    struct sockaddr_in addr;
    int addrlen, fd;
    chordMessager::chordMessageDetectNode detect_msg(serviceChordNode->thisNode, node_t(),serviceChordNode->thisNode);
    std::string msg_serialized = detect_msg.serialize();
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
      throw ERRORS::chordServiceSocketCreateFail();
    }
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVICE_DETECT_PORT);
    addrlen = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(GROUP_IP);
    for (int i = 0; i < SERVICE_DETECT_RETRY_TIME; ++i) {
      DEBUG_PRINT("chordService is sending detect node messages...");
      if (serviceChordNode->gotDetectNodeResponse) {
        //chordNode has received bound back message
        break;
      }
      sendto(fd, msg_serialized.c_str(), msg_serialized.size(), 0, (struct sockaddr*)&addr, addrlen);
      //sleep for 5 seconds
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    if (!serviceChordNode->gotDetectNodeResponse) {
      //this is the first node in the network
      //ask chordnode to do self fingertable update
      DEBUG_PRINT("this chord node is the first in the network.");
      node_t dummy;
      serviceChordNode->join(dummy);
    }
    close(fd);
  }

  void chordService::detectNodesResponse() {
    DEBUG_PRINT("chord service starts detect nodes response process.");
    struct sockaddr_in addr;
    int fd;
    socklen_t addrlen;
    struct ip_mreq mreq;
    char message[100];
    char prefix[20];
    std::string prefix_str;
    sprintf(prefix, "type:%d", chordMessager::chordMessageType::messageDetectNode);
    prefix_str = std::string(prefix);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
      throw ERRORS::chordServiceSocketCreateFail();
    }
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVICE_DETECT_PORT_BIND);
    addrlen = sizeof(addr);
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
      throw ERRORS::chordServiceSocketBindFail();
    }
    mreq.imr_multiaddr.s_addr = inet_addr(GROUP_IP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
      throw ERRORS::chordServiceSetSocketOptFail();
    }
    while (true) {
      ssize_t cnt = recvfrom(fd, message, sizeof(message), 0, (struct sockaddr*)&addr, &addrlen);
      if (cnt < 0) {
        throw ERRORS::chordServiceRecvfromFail();
      }else if (cnt > 0) {
        std::string message_str(message);
        if (message_str.find(prefix_str) == 0) {
          //this is a detectNode message
          //return this node info back to the source
          chordMessager::chordMessageBase* inmsg = nullptr;
          chordMessager::chordMessager::deserializeMessage(message_str, inmsg);
          chordMessager::chordMessageDetectNodeResponse* outmsg = new chordMessager::chordMessageDetectNodeResponse(serviceChordNode->thisNode, inmsg->getNodeParam()[0], serviceChordNode->thisNode);
          //printf("%s\n",outmsg->serialize().c_str());
          delete inmsg;
          inmsg = nullptr;
          serviceChordNode->makeRequest(outmsg, inmsg);
          delete inmsg;
        }
      }
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  }

  bool chordService::isInitialized() {
    return initialized;
  }

  void chordService::dumpFingerTable() {
    serviceChordNode->dumpFingerTable();
  }

  void chordService::closeService() {
    DEBUG_PRINT("Closing service");
    delete serviceInstance;
    delete serviceChordNode;
    delete serviceDispatcher;
    //delete serviceDispatcherThread;
    //delete serviceDetectNodesResponseThread;
  }

  std::string chordService::getBaseName(std::string fpath) {
    size_t i = fpath.find_last_of("/\\");
    return fpath.substr(i + 1);
  }

  //set working directory
  void chordService::setWorkingDir(std::string dir) {
    serviceChordNode->datapath = dir;
  }

  //store a file to the chord network
  void chordService::storeFile(std::string fpath) {
    try {
      std::ifstream is(fpath, std::ifstream::binary);
      if (!is) {
        throw ERRORS::chordFileOpenFail();
      }
      std::string basename = getBaseName(fpath);
      is.seekg(0, is.end);
      int size = is.tellg();
      is.seekg(0, is.beg);
      serviceChordNode->storeKeyValue(basename, is, size);
      is.close();
      printf("file save success!\n");
    } catch (ERRORS::chordFileOpenFail) {
      printf("file does not exist!\n");
    }
  }

  //delete a file from the chord network
  void chordService::deleteFile(std::string basename) {
    serviceChordNode->removeKey(basename);
  }

  //check the existence of a file
  bool chordService::existFile(std::string basename) {
    return serviceChordNode->hasKey(basename);
  }

  //get a file from the chord network
  void chordService::getFile(std::string basename) {
    if (!existFile(basename)) {
      return;
    }
    serviceChordNode->fetchKeyValue(basename);
  }

  //list all the files in the chord network
  std::vector<std::string> chordService::listFile() {
    return serviceChordNode->getGlobalStoredKeys();
  }

}
