//
//  chordMessageDispatcher.cpp
//  chord
//
//  Created by Haoliang on 11/25/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "chordMessageDispatcher.h"

namespace CHORD {
  chordNode* chordMessageDispatcher::thisNode = nullptr;
  std::thread* chordMessageDispatcher::dispatchThread = nullptr;
  std::queue<std::thread*> chordMessageDispatcher::threadQueue;
  std::mutex chordMessageDispatcher::threadQueueLock;
  std::thread* chordMessageDispatcher::threadCleaner = nullptr;

  chordMessageDispatcher::chordMessageDispatcher(CHORD::chordNode* _thisNode) {
    DEBUG_PRINT("Creating chordMessageDispatcher");
    thisNode = _thisNode;
    listener.setMode(0);
    listener.setPortno(thisNode->getDispatcherPortno());
    threadCleaner = new std::thread(cleanThread);
    listener.init();
  }

  chordMessageDispatcher::~chordMessageDispatcher() {
    //threadCleaner->detach();
    //delete threadCleaner;
  }

  void chordMessageDispatcher::cleanThread() {
    while (1) {
      threadQueueLock.lock();
      while (!threadQueue.empty()) {
        std::thread* th = threadQueue.front();
        threadQueue.pop();
        if (th->joinable()) {
          th->join();
        }
        delete th;
      }
      threadQueueLock.unlock();
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  }

  //the chordMessageDispatcher runs an infinite loop
  void chordMessageDispatcher::startListen() {
    DEBUG_PRINT("chordMessageDispatcher starts listen.");
    while (true) {
      int newsockfd = listener.startListenLoop();
      dispatchThread = new std::thread(dispatchRequest, newsockfd);
      threadQueueLock.lock();
      threadQueue.push(dispatchThread);
      threadQueueLock.unlock();
    }
  }

  void chordMessageDispatcher::dispatchRequest(int newsockfd) {
    DEBUG_PRINT("chordMessageDispatcher is dispatching request.");
    int newmessager = thisNode->getUsableMessager();
    if (newmessager == -1) {
      throw ERRORS::chordMessagerNoUsableMessager();
    }
    thisNode->messagerPool[newmessager].setSocketFileDescriptor(newsockfd);
    std::string msg = thisNode->messagerPool[newmessager].readMessage();
    chordMessager::chordMessageBase *inmsg = nullptr, *outmsg = nullptr;
    thisNode->messagerPool[newmessager].deserializeMessage(msg, inmsg);
    thisNode->executeChordMessage(inmsg, outmsg, newmessager);
    std::string serialized_msg = outmsg->serialize();
    thisNode->messagerPool[newmessager].sendMessage(serialized_msg);
    delete inmsg;
    delete outmsg;
    //free messager
    thisNode->freeMessager(newmessager);
  }

  bool chordMessageDispatcher::isListenning() {
    return listener.isListenning;
  }
}
