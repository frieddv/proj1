//
// Created by frieddv on 12/25/18.
//
#define NUM_OF_ARGS 23

#include "DataReader.h"
#include "VariableManager.h"
#include "OpenDataServerCmd.h"

#include <vector>
#include <sstream>
#include <netinet/in.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <cstring>

using namespace std;

void setInputSymbols(string line, VariableManager *variableManager) {
    vector<double> lineArgs;
    char *copyString;
    const char *asCharArr = line.c_str();
    char copy[strlen(asCharArr)];
    strcpy(copy, asCharArr);
    copyString = strtok(copy, ","); //from the net whole while loop
    while (copyString != NULL) {
        lineArgs.push_back(stod(copyString)); //insert current token to vector
        copyString = strtok(NULL, ","); //go to next token
    }
    for (int i = 0; i < NUM_OF_ARGS; ++i) { //max args = 23
        switch (i) {
            case 0:
                variableManager->SetIndices("instrumentation/airspeed-indicator/indicated-speed-kt", lineArgs.at(0));
                break;
            case 1:
                variableManager->SetIndices("instrumentation/altimeter/indicated-altitude-ft", lineArgs.at(1));
                break;
            case 2:
                variableManager->SetIndices("instrumentation/altimeter/indicated-altitude-ft", lineArgs.at(2));
                break;
            case 3:
                variableManager->SetIndices("instrumentation/attitude-indicator/indicated-pitch-deg", lineArgs.at(3));
                break;
            case 4:
                variableManager->SetIndices("instrumentation/attitude-indicator/indicated-roll-deg", lineArgs.at(4));
                break;
            case 5:
                variableManager->SetIndices("instrumentation/attitude-indicator/internal-pitch-deg", lineArgs.at(5));
                break;
            case 6:
                variableManager->SetIndices("instrumentation/attitude-indicator/internal-roll-deg", lineArgs.at(6));
                break;
            case 7:
                variableManager->SetIndices("instrumentation/encoder/indicated-altitude-ft", lineArgs.at(7));
                break;
            case 8:
                variableManager->SetIndices("instrumentation/encoder/pressure-alt-ft", lineArgs.at(8));
                break;
            case 9:
                variableManager->SetIndices("instrumentation/gps/indicated-altitude-ft", lineArgs.at(9));
                break;
            case 10:
                variableManager->SetIndices("instrumentation/gps/indicated-ground-speed-kt", lineArgs.at(10));
                break;
            case 11:
                variableManager->SetIndices("instrumentation/gps/indicated-vertical-speed", lineArgs.at(11));
                break;
            case 12:
                variableManager->SetIndices("instrumentation/heading-indicator/indicated-heading-deg", lineArgs.at(12));
                break;
            case 13:
                variableManager->SetIndices("instrumentation/magnetic-compass/indicated-heading-deg", lineArgs.at(13));
                break;
            case 14:
                variableManager->SetIndices("instrumentation/slip-skid-ball/indicated-slip-skid", lineArgs.at(14));
                break;
            case 15:
                variableManager->SetIndices("instrumentation/turn-indicator/indicated-turn-rate", lineArgs.at(15));
                break;
            case 16:
                variableManager->SetIndices("instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                                            lineArgs.at(16));
                break;
            case 17:
                variableManager->SetIndices("controls/flight/aileron", lineArgs.at(17));
                break;
            case 18:
                variableManager->SetIndices("controls/flight/elevator", lineArgs.at(18));
                break;
            case 19:
                variableManager->SetIndices("controls/flight/rudder", lineArgs.at(19));
                break;
            case 20:
                variableManager->SetIndices("controls/flight/flaps", lineArgs.at(20));
                break;
            case 21:
                variableManager->SetIndices("controls/engines/engine/throttle", lineArgs.at(21));
                break;
            case 22:
                variableManager->SetIndices("engines/engine/rpm", lineArgs.at(22));
                break;
            default:
                break;
        }
    }

}

void* DataReader::OpenDataServer(void *arg) {
    Input *params = (Input *) arg;
    vector<int> sockets;

    int socketFd; // main socket fileDescriptor
    int newsockfd; // new socket fileDescriptor
    int clilen;

    struct sockaddr_in serv_addr, cli_addr;

    //creating socket object
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    //if creation failed
    if (socketFd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    sockets.push_back(socketFd);

    //Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET; // tcp server
    serv_addr.sin_addr.s_addr = INADDR_ANY; //server ip (0.0.0.0 for all incoming connections)
    serv_addr.sin_port = htons(params->portNum); //init server port

    //bind the host address using bind() call
    if (bind(socketFd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        //if binding faild
        perror("ERROR on binding");
        exit(1);
    }


    //start listening for the clients using the main socket
    listen(socketFd, 1);
    clilen = sizeof(cli_addr);


    //accept actual connection from the client
    newsockfd = accept(socketFd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);


    sockets.push_back(newsockfd);


    //if connections with the client failed
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }


    string dataStr;

    while (!params->variableManager->IsThreadFinished(MAIN)) {
        char buf[1024];
        int numBytesRead = recv(newsockfd, buf, sizeof(buf), 0);


        if (numBytesRead > 0) {
            for (int i = 0; i < numBytesRead; i++) {
                char c = buf[i];
                if (c == '\n') {
                    if (dataStr.length() > 0) {
                        params->variableManager->ConnectedToServer();
                        setInputSymbols(dataStr, params->variableManager);
                        //this_thread::sleep_for(chrono::milliseconds(1000/params->NumToSec));
                        dataStr = "";
                    }
                } else dataStr += c;
            }
        } else {
            break;
        }
    }
    for (int socket : sockets)
        close(socket);
    params->variableManager->ThreadFinished(SERVER);
    return nullptr;
}