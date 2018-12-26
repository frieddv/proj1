//
// Created by frieddv on 12/25/18.
//
#define NUM_OF_ARGS 23

#include "DataReader.h"
#include "VariableManager.h"

#include <vector>
#include <sstream>
#include <netinet/in.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <cstring>

using namespace std;


void DataReader :: connectToClient(int portNumber, int hz, VariableManager *variableManager){
    struct sockaddr_in serverAddress, clientAddress;
    int clientSocket = 0;
    int n;
    mutex mtx;
    // Trying to connect.
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        exit(1);
    }
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNumber);
    /* Now bind the host address using bind() call.*/
    if (bind(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        perror("Error: binding failed.");

    listen(clientSocket, 5);
    int clientLength = sizeof(clientAddress);
    /* Accept actual connection from the client */
    int newsockfd = accept(clientSocket, (struct sockaddr *) &clientAddress, (socklen_t *) &clientLength);

    if (newsockfd < 0) {
        perror("Error: failed in acception.");
        exit(1);
    }
    char buffer [1000];
    char bufferBackUp [1000];
    int readingText;

    mtx.lock(); //critic code = we don't want that something will change the maps while we there.

    bzero(buffer, 1000);
    n = read(newsockfd, buffer, 999); //read line from simulator to socket.

    //backup for buffer.
    strcpy(bufferBackUp ,buffer);


    vector<double> lineArgs;
    char* copyString;
    copyString=strtok(buffer, ","); //from the net whole while loop
    while (copyString != NULL) {
        lineArgs.push_back(stod(copyString)); //insert current token to vector
        copyString = strtok(NULL, ","); //go to next token
    }

    for (int i = 0; i < NUM_OF_ARGS; ++i) { //max args = 23



        switch (i) {
            case 0:
                variableManager->setIndices("instrumentation/airspeed-indicator/indicated-speed-kt", lineArgs.at(0));
                break;
            case 1:
                variableManager->setIndices("instrumentation/altimeter/indicated-altitude-ft",lineArgs.at(1));
                break;
            case 2:
                variableManager->setIndices("instrumentation/altimeter/indicated-altitude-ft",lineArgs.at(2));
                break;
            case 3:
                variableManager->setIndices("instrumentation/attitude-indicator/indicated-pitch-deg",lineArgs.at(3));
                break;
            case 4:
                variableManager->setIndices("instrumentation/attitude-indicator/indicated-roll-deg", lineArgs.at(4));
                break;
            case 5:
                variableManager->setIndices("instrumentation/attitude-indicator/internal-pitch-deg", lineArgs.at(5));
                break;
            case 6:
                variableManager->setIndices("instrumentation/attitude-indicator/internal-roll-deg", lineArgs.at(6));
                break;
            case 7:
                variableManager->setIndices("instrumentation/encoder/indicated-altitude-ft", lineArgs.at(7));
                break;
            case 8:
                variableManager->setIndices("instrumentation/encoder/pressure-alt-ft", lineArgs.at(8));
                break;
            case 9:
                variableManager->setIndices("instrumentation/gps/indicated-altitude-ft", lineArgs.at(9));
                break;
            case 10:
                variableManager->setIndices("instrumentation/gps/indicated-ground-speed-kt", lineArgs.at(10));
                break;
            case 11:
                variableManager->setIndices("instrumentation/gps/indicated-vertical-speed", lineArgs.at(11));
                break;
            case 12:
                variableManager->setIndices("instrumentation/heading-indicator/indicated-heading-deg", lineArgs.at(12));
                break;
            case 13:
                variableManager->setIndices("instrumentation/magnetic-compass/indicated-heading-deg", lineArgs.at(13));
                break;
            case 14:
                variableManager->setIndices("instrumentation/slip-skid-ball/indicated-slip-skid", lineArgs.at(14));
                break;
            case 15:
                variableManager->setIndices("instrumentation/turn-indicator/indicated-turn-rate", lineArgs.at(15));
                break;
            case 16:
                variableManager->setIndices("instrumentation/vertical-speed-indicator/indicated-speed-fpm", lineArgs.at(16));
                break;
            case 17:
                variableManager->setIndices("controls/flight/aileron", lineArgs.at(17));
                break;
            case 18:
                variableManager->setIndices("controls/flight/elevator", lineArgs.at(18));
                break;
            case 19:
                variableManager->setIndices("controls/flight/rudder", lineArgs.at(19));
                break;
            case 20:
                variableManager->setIndices("controls/flight/flaps", lineArgs.at(20));
                break;
            case 21:
                variableManager->setIndices("controls/engines/engine/throttle",  lineArgs.at(21));
                break;
            case 22:
                variableManager->setIndices("engines/engine/rpm", lineArgs.at(22));
                break;
            default:
                break;
        }
    }
}