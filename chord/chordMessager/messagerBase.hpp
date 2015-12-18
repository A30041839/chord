//
//  messagerBase.hpp
//  chord
//
//  Created by Haoliang on 11/29/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef messagerBase_hpp
#define messagerBase_hpp

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <thread>
#include <chrono>
#include "../errors.h"
#include "debug.h"
#include "types.h"

namespace chordMessager {
    enum CHORD_MESSAGER_MODE {
        SERVER = 0,
        CLIENT
    };
    
    class messagerBase {
    public:
        int sockfd;
        int portno;
        socklen_t clilen;
        char buffer[MESSAGER_BUFFER_SIZE];
        struct sockaddr_in serv_addr;
        struct sockaddr_in cli_addr;
        struct hostent *server;
        std::string remote_host;
        int remote_portno;
        int mode;
        int busy;
        
        messagerBase(){};
        //destructor
        ~messagerBase();
        void setMode(int);
        void setPortno(int);
        void setRemoteHost(std::string);
        void setRemotePort(int);
        void startListen();
        void startConnect();
        //init
        void init();
        void initServer();
        void initClient();
        //send message
        void sendMessage(std::string);
        //read message
        std::string readMessage();
        void makeBusy();
        void makeFree();
        void closeConnection();
    };
}

#endif /* messagerBase_hpp */
