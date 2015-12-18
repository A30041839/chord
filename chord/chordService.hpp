//
//  chordService.hpp
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef chordService_hpp
#define chordService_hpp

#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "chordNode.hpp"
#include "chordMessageDispatcher.hpp"
#include "chordMessager/chordMessage.hpp"
#include "errors.h"
#include "debug.h"
#include "types.h"

namespace CHORD {
    //singleton
    class chordService {
        chordService();
        static chordService* serviceInstance;
        static chordMessageDispatcher *serviceDispatcher;
        static chordNode *serviceChordNode;
        static std::thread* serviceDispatcherThread;
        static std::thread* serviceDetectNodesResponseThread;
        static void startDispatcher();
        static void detectNodes();
        static void detectNodesResponse();
        static bool initialized;
    public:
        static chordService* createService(std::string hostname, int portno, std::string machine_name);
        static chordService* getServiceInstance();
        static bool isInitialized();
        static void dumpFingerTable();
        static void closeService();
        
        std::string getBaseName(std::string);

        //set working directory
        void setWorkingDir(std::string dir);
        //store a file to the chord network
        void storeFile(std::string fpath);
        //delete a file from the chord network
        void deleteFile(std::string fname);
        //check the existence of a file
        bool existFile(std::string basename);
        //get a file from the chord network
        void getFile(std::string fname);
        //list all the files in the chord network
        std::vector<std::string> listFile();
    };
}

#endif /* chordService_hpp */
