//
//  chordMessager.h
//  chordMessager
//
//  Created by Haoliang on 11/24/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordMessager_h
#define chordMessager_h

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <strings.h>
#include <unistd.h>
#include "chordMessage.h"
#include "messagerBase.h"
#include "../debug.h"
#include "../errors.h"

namespace chordMessager {
  class chordMessager : public messagerBase {
    public:
      bool isListenning = false;
      int startListenLoop();
      void setSocketFileDescriptor(int sockfd);
      static void deserializeMessage(std::string, chordMessageBase*&);

      void sendData(std::ifstream&, int data_size);
      void receiveData(std::ofstream&, int data_size);
  };

}//end of namespace chordMessager

#endif /* chordMessager_h */
