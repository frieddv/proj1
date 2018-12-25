//
// Created by frieddv on 12/25/18.
//

#include "DataReader.h"
#include "VariableManager.h"

#include <vector>
#include <sstream>
#include <netinet/in.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>

using namespace std;


void DataReader :: connectToClient(int portNumber, int hz, VariableManager *variableManager){
    struct sockaddr_in serverAddress, clientAddress;
    int clientSocket = 0;
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
    char buffer[256];
    int readingText;

    while(true){
        /* If connection is established then start communicating */
        cout<<"The client sent: "<<endl;
        bzero(buffer, 256);
        read(newsockfd, buffer, 255);

        if (readingText < 0) {
            perror("ERROR reading from socket");

        }
        usleep(1 / hz);
        string output;
        vector<string> bufferSplit;
        std::istringstream line_stream(buffer);
        while (std::getline(line_stream, output, ',')) // line parsing
            bufferSplit.push_back(output);
        cout << buffer << endl;
        for (map<string, double >::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it)
            singleton->setValue(const_cast<string &>(it->first),stoi(bufferSplit.at(dictionaryPlacement->getValue(it->first))),"server");
    }
}