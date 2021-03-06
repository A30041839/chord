//
//  chordMessageDispatcher.h
//  chord
//
//  Created by Haoliang on 11/25/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordMessageDispatcher_h
#define chordMessageDispatcher_h

#include <stdio.h>
#include <thread>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <queue>
#include <chrono>
#include <mutex>
#include "chordMessager/chordMessage.h"
#include "chordMessager/chordMessager.h"
#include "chordNode.h"
#include "debug.h"
#include "types.h"

namespace CHORD {

  class chordMessageDispatcher {
    public:
      chordMessager::chordMessager listener;
      chordMessageDispatcher(chordNode*);
      ~chordMessageDispatcher();
      static std::queue<std::thread*> threadQueue;
      static std::mutex threadQueueLock;
      static std::thread* threadCleaner;
      static chordNode* thisNode;
      static std::thread* dispatchThread;
      void startListen();
      static void dispatchRequest(int);
      static void cleanThread();
      bool isListenning();
  };
}

#endif /* chordMessageDispatcher_h */
