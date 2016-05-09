//
//  types.h
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef types_h
#define types_h

#define SERVICE_DISP_PORT 2000
#define SERVICE_RPC_PORT 2001
#define CHORDNODE_PORT_OFFSET 2002
#define CHORD_DISK_PATH "/home/haoliang/chord/test/chord_disk/"
#define CHORD_INPUT_PATH "/home/haoliang/chord/test/chord_input_files/"
#define SERVICE_DETECT_PORT_BIND 5000
#define MACHINE_NAME "OrangeJuice"


#define IDENTIFIER_LEN 32
#define GROUP_IP "224.0.0.1"
#define SERVICE_HOSTNAME "0.0.0.0"
#define SERVICE_DETECT_PORT 5000
#define SERVICE_DETECT_RETRY_TIME 3
#define CHORDNODE_MESSAGER_POOL_SIZE 256
#define MESSAGER_BUFFER_SIZE 5000


typedef long long unsigned int identifier_t;

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
  int portno_disp;
  int portno_rpc;
  std::string machine_name;

  node_t(): hostname(""), identifier(0), portno_disp(0), portno_rpc(0), machine_name("") {}

  node_t(std::string _hostname, identifier_t _identifier, int _portno_disp, int _portno_rpc, std::string _machine_name):
    hostname(_hostname), identifier(_identifier), portno_disp(_portno_disp), portno_rpc(_portno_rpc), machine_name(_machine_name) {}

  bool operator==(const node_t& other) {
    return hostname == other.hostname
      and identifier == other.identifier
      and portno_disp == other.portno_disp
      and portno_rpc == other.portno_rpc
      and machine_name == other.machine_name;
  }

  bool operator!=(const node_t& other) {
    return !operator==(other);
  }

  std::string to_string() {
    char buf[200];
    sprintf(buf, "hostname:%s|identifier:%llu|portno_disp:%d|portno_rpc:%d|machine_name:%s|", hostname.c_str(), identifier, portno_disp, portno_rpc, machine_name.c_str());
    return std::string(buf);
  }
};

#endif /* types_h */
