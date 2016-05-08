//
//  utils.h
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include "sha1.h"
#include "types.h"

static std::unordered_map<char, std::string> hex_to_bin = {
  {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
  {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
  {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
  {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
};

static std::unordered_map<char, int> hex_to_dec = {
  {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
  {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
  {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11},
  {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15},
};

inline int inRange(identifier_t id, identifier_t low, identifier_t high) {
  //check if id lies in [low, high]
  if (low > high) {
    return id <= high or id >= low;
  }else {
    return id >= low and id <= high;
  }
}

inline std::string sha1_hex_to_bin(std::string sha1_hex) {
  std::string bin;
  for (int i = 0; i < (int)sha1_hex.size(); ++i) {
    bin.append(hex_to_bin[sha1_hex[i]]);
  }
  return bin;
}

inline int compareSHA1(std::string sha1_hex_1, std::string sha1_hex_2) {
  //convert to binary
  std::string sha1_bin_1 = sha1_hex_to_bin(sha1_hex_1);
  std::string sha1_bin_2 = sha1_hex_to_bin(sha1_hex_2);
  if (sha1_bin_1 == sha1_bin_2) {
    return 0;
  }else {
    return sha1_bin_1 < sha1_bin_2 ? -1 : 1;
  }
}

inline identifier_t getHashcode(std::string valuetoHash) {
  if (valuetoHash.empty()) {
    throw ERRORS::argumentEmpty();
  }
  const char* src = valuetoHash.c_str();
  unsigned int length = (unsigned int)valuetoHash.size();
  unsigned char* hashcode = new unsigned char[20];
  sha1::calc(src, length, hashcode);
  char* hex = new char[50];
  sha1::toHexString(hashcode, hex);
  //we only keep the lower 32 bits of sha1
  identifier_t hash;
  int n = (int)strlen(hex);
  for (int i = n - 8; i < n; ++i) {
    hash <<= 4;
    hash += hex_to_dec[hex[i]];
  }
  return hash;
}

inline std::vector<std::string> splitStr(const std::string& str, char delim) {
  std::istringstream iss(str);
  std::vector<std::string> res;
  std::string tmp;
  while (getline(iss, tmp, delim)) {
    res.push_back(tmp);
  }
  return res;
}

#endif /* utils_h */
