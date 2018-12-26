//
// Created by frieddv on 12/26/18.
//

#include "ConnectToClient.h"
#include "ConnectCmd.h"

void *ConnectToClient(void *args) {

    int sockfd;
    ConnectInput* params = (ConnectInput*) args;
    vector<int> sockets;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    sockets.push_back(sockfd);

    int len = params->IP.size();
    char char_array[len + 1];
    strcpy(char_array, params->IP.c_str());
    server = gethostbyname(char_array);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }




    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(params->portNum);


    // connect to the server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    while (!params->variableManager->IsThreadFinished(MAIN)) {
        //todo change the function, basiclly equivalent to IsUpdatePending()
        if (params->variableManager->IsUpdatePending()){

            // parameters to send - the stuff needed to be sent
            pair<string, double> toSend = params->variableManager->PopPendingUpdate();
            //returns iterator to the map of binding stuff
            string path = toSend.first;
            double value = toSend.second;

            // creating the message
            string message = "set " + path + " " + to_string(value) + "\r\n";

            ssize_t n;

            // Send message to the server
            n = write(sockfd, message.c_str(), message.length());

            if (n < 0) {
                break;
            }
        }
    }
    /* Now ask for a message from the user, this message
    * will be read by server
    */

    for (int socket : sockets) {
        close(socket);
    }
    params->variableManager->ThreadFinished(CLIENT);
    return nullptr;
}
