//
//  chordMessager.hpp
//  chordMessager
//
//  Created by Haoliang on 11/24/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordMessager_hpp
#define chordMessager_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "chordMessage.hpp"
#include "messagerBase.hpp"
#include "debug.h"
#include "../errors.h"

namespace chordMessager {
    class chordMessager : public messagerBase {
    public:
        int startListenLoop();
        void setSocketFileDescriptor(int sockfd);
        static void deserializeMessage(std::string, chordMessageBase*&);
        
        void sendData(std::ifstream&, int data_size);
        void receiveData(std::ofstream&, int data_size);
    };
        
}//end of namespace chordMessager

#endif /* chordMessager_hpp */
