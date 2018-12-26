//
// Created by frieddv on 12/26/18.
//

#include "ConnectCmd.h"
#include "ConnectToClient.h"


void ConnectCmd::DoCommand() {
    ConnectInput *connectInput = new ConnectInput();
    connectInput->portNum = (int)port->Calculate();
    connectInput->IP = IP;
    connectInput->variableManager = variableManager;
    variableManager->ThreadStarted(CLIENT);
    pthread_t thread;
    pthread_create(&thread, nullptr, ConnectClient, connectInput);
}

void *ConnectCmd::ConnectClient(void *input) {
    ConnectToClient(input);
    delete ((ConnectInput*)input);
    return nullptr;
}
