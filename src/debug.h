//
//  debug.h
//  chord
//
//  Created by Haoliang on 11/26/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef debug_h
#define debug_h

#include <ctime>
#include <string>
#include <iostream>

inline std::string getCurrentTime() {
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return std::string(buf);
}

inline void DEBUG_PRINT(const char* info) {
  std::cout << "[" << getCurrentTime() << "]:" <<  info << std::endl;
}

#endif /* debug_h */
