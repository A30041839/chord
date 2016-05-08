//
//  errors.h
//  chord
//
//  Created by Haoliang on 11/23/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#ifndef errors_h
#define errors_h
#include <exception>

namespace ERRORS {
  struct argumentEmpty : std::exception {
    const char* what() const noexcept {return "Passed in argument is empty!\n";}
  };
  struct chordMessagerSocketCreateFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket create failed!\n";}
  };
  struct chordMessagerGetHostFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket get host failed!\n";}
  };
  struct chordMessagerConnectFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket connect to server failed!\n";}
  };
  struct chordMessagerSocketReadFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket read failed!\n";}
  };
  struct chordMessagerSocketWriteFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket write failed!\n";}
  };
  struct chordMessagerSocketBindFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket bind failed!\n";}
  };
  struct chordMessagerSocketAcceptFail : std::exception {
    const char* what() const noexcept {return "ChordMessager socket accept failed!\n";}
  };
  struct chordMessagerUnknownMode : std::exception {
    const char* what() const noexcept {return "ChordMessager unkown mode!\n";}
  };
  struct chordMessagerNoUsablePortno : std::exception {
    const char* what() const noexcept {return "ChordMessager can't allocate free port number!\n";}
  };
  struct chordMessagerNoUsableMessager : std::exception {
    const char* what() const noexcept {return "ChordMessageDispatcher can't allocate free messager!\n";}
  };
  struct chordServiceNotInitiated : std::exception {
    const char* what() const noexcept {return "Chord service is not initiated, create it first!\n";}
  };
  struct chordMessagerUnknownMessageType : std::exception {
    const char* what() const noexcept {return "Unkown chord message type!\n";}
  };
  struct chordServiceSocketCreateFail : std::exception {
    const char* what() const noexcept {return "Chord service socket create failed!\n";}
  };
  struct chordServiceSocketBindFail : std::exception {
    const char* what() const noexcept {return "Chord service socket bind failed!\n";}
  };
  struct chordServiceSetSocketOptFail : std::exception {
    const char* what() const noexcept {return "Chord service setsockopt failed!\n";}
  };
  struct chordServiceRecvfromFail : std::exception {
    const char* what() const noexcept {return "Chord service recvfrom failed!\n";}
  };
  struct chordFileOpenFail : std::exception {
    const char* what() const noexcept {return "Chord open file failed!\n";}
  };
  struct chordFileCreateFail : std::exception {
    const char* what() const noexcept {return "Chord create file failed!\n";}
  };
  struct chordSendFileFail : std::exception {
    const char* what() const noexcept {return "Chord send file failed!\n";}
  };
  struct chordRPCFail : std::exception {
    const char* what() const noexcept {return "chord RPC call failed!\n";}
  };
}//namespace ERRORS

#endif /* errors_h */
