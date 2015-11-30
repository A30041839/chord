//
//  messagerBase.cpp
//  chord
//
//  Created by Haoliang on 11/29/15.
//  Copyright © 2015 Haoliang. All rights reserved.
//

#include "messagerBase.hpp"

namespace chordMessager {
    messagerBase::~messagerBase() {
        close(sockfd);
    }
    
    void messagerBase::initServer() {
        DEBUG_PRINT("Init server");
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            throw ERRORS::chordMessagerSocketCreateFail();
        }
        bzero((char*) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(portno);
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
            throw ERRORS::chordMessagerSocketBindFail();
        }
    }
    
    void messagerBase::initClient() {
        DEBUG_PRINT("Init client");
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            throw ERRORS::chordMessagerSocketCreateFail();
        }
        server = gethostbyname(remote_host.c_str());
        if (server == NULL) {
            throw ERRORS::chordMessagerGetHostFail();
        }
        bzero((char*) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(remote_portno);
    }
    
    void messagerBase::init() {
        if (mode == CHORD_MESSAGER_MODE::SERVER) {
            try {
                initServer();
            } catch (ERRORS::chordMessagerSocketCreateFail) {
                close(sockfd);
                initServer();
            }
        }else if (mode == CHORD_MESSAGER_MODE::CLIENT) {
            try {
                initClient();
            } catch (ERRORS::chordMessagerSocketCreateFail) {
                close(sockfd);
                initClient();
            }
        }else {
            throw ERRORS::chordMessagerUnknownMode();
        }
    }
    
    void messagerBase::startConnect() {
        DEBUG_PRINT("Try connect");
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            throw ERRORS::chordMessagerConnectFail();
        }
    }
    
    void messagerBase::setMode(int _mode) {
        mode = _mode;
    }
    
    void messagerBase::setPortno(int _portno) {
        portno = _portno;
    }
    
    void messagerBase::setRemoteHost(std::string _remote_host) {
        remote_host = _remote_host;
    }
    
    void messagerBase::setRemotePort(int _remote_portno) {
        remote_portno = _remote_portno;
    }
    
    void messagerBase::startListen() {
        DEBUG_PRINT("Start listen");
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
        int newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
        if (newsockfd < 0) {
            throw ERRORS::chordMessagerSocketAcceptFail();
        }
        close(sockfd);
        sockfd = newsockfd;
    }
    
    std::string messagerBase::readMessage() {
        DEBUG_PRINT("Reading message");
        bzero(buffer, MESSAGER_BUFFER_SIZE);
        ssize_t n = read(sockfd, buffer, MESSAGER_BUFFER_SIZE);
        if (n < 0) {
            throw ERRORS::chordMessagerSocketReadFail();
        }
        std::string msg(buffer);
        return msg;
    }
    
    void messagerBase::sendMessage(std::string msg) {
        DEBUG_PRINT("Sending message");
        bzero(buffer, MESSAGER_BUFFER_SIZE);
        bcopy((char*)msg.c_str(), (char*)buffer, msg.size());
        ssize_t n = write(sockfd, buffer, msg.size());
        if (n < 0) {
            throw ERRORS::chordMessagerSocketWriteFail();
        }
    }
    
    void messagerBase::makeBusy() {
        busy = 1;
    }
    
    void messagerBase::makeFree() {
        busy = 0;
    }
    
    void messagerBase::closeConnection() {
        DEBUG_PRINT("Connection closed");
        close(sockfd);
    }
}