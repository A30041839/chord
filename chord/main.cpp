//
//  main.cpp
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "chordService.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    CHORD::chordService* service = CHORD::chordService::createService(SERVICE_HOSTNAME, SERVICE_PORT);
    
    string cmd;
    service->setWorkingDir(CHORD_DISK_PATH);
    
    cout << "please type in your commands here:" << endl;
    cout << "dump: show the finger table." << endl;
    cout << "list: show all of the files in the chord network" << endl;
    cout << "save: save a file to the network" << endl;
    cout << "leave: make yourself leave the network" << endl;
    
    while (cin >> cmd) {
        if (cmd == "dump") {
            service->dumpFingerTable();
        }else if (cmd == "list") {
            vector<string> allfiles = service->listFile();
            for (string file : allfiles) {
                cout << file << endl;
            }
        }else if (cmd == "save") {
            std::string fname;
            cin >> fname;
            service->storeFile(CHORD_INPUT_PATH + fname);
        }else if (cmd == "leave") {
            service->closeService();
        }
    }
    return 0;
}