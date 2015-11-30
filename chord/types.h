//
//  types.h
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef types_h
#define types_h

#define IDENTIFIER_LEN 32
#define GROUP_IP "224.0.0.1"

#define SERVICE_PORT 2000
#define SERVICE_HOSTNAME "172.27.156.63"
#define SERVICE_DETECT_PORT 5000
#define SERVICE_DETECT_RETRY_TIME 5

#define CHORDNODE_MESSAGER_POOL_SIZE 256
#define CHORDNODE_PORT_OFFSET 2001

#define MESSAGER_BUFFER_SIZE 2048

#define CHORD_DISK_PATH "/Users/haoliang/Desktop/chorddisk/"
#define CHORD_INPUT_PATH "/Users/haoliang/Desktop/chord_input_files/"

//DEBUG MACRO//
#define SERVICE_DETECT_PORT_BIND 5000
#define HASH_CODE_OFFSET 0

typedef long long int identifier_t;

#include <string>
#include <vector>

struct file_t {
    std::string file_name;
    int file_size;
    std::string create_time;
    std::string owner;
};

struct fsinfo_t {
    std::string work_dir;
    int file_cnt;
    std::vector<file_t> files;
};

struct node_t {
    std::string hostname;
    identifier_t identifier;
    int portno;
    
    node_t(): hostname(""), identifier(0), portno(0) {}
    
    node_t(std::string _hostname, identifier_t _identifier, int _portno):
    hostname(_hostname), identifier(_identifier), portno(_portno) {}
    
    bool operator==(const node_t& other) {
        return hostname == other.hostname
        and identifier == other.identifier
        and portno == other.portno;
    }
    
    bool operator!=(const node_t& other) {
        return !operator==(other);
    }
    
    std::string to_string() {
        char buf[200];
        sprintf(buf, "hostname:%s|identifier:%lld|portno:%d|", hostname.c_str(), identifier, portno);
        return std::string(buf);
    }
};

#endif /* types_h */
