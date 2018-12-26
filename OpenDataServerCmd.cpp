//
// Created by frieddv on 12/25/18.
//

#include <vector>
#include "OpenDataServerCmd.h"
#include "DataReader.h"

void* OpenDataServerCmd::OpenServer(void* input) {
    DataReader dataReader;
    Input* input1 = (Input*)input;
    dataReader.connectToClient(input1->portNum, input1->hz, input1->variableManager);
}

OpenDataServerCmd::OpenDataServerCmd(VariableManager *variableManager, IExpression *portNo, IExpression *hz)
        : variableManager(variableManager), portNo(portNo), hz(hz) {}

void OpenDataServerCmd::DoCommand() {
    Input *input = new Input();
    input->portNum = (int)portNo->Calculate();
    input->hz = (int)hz->Calculate();
    input->variableManager = variableManager;
    variableManager->ThreadStarted(SERVER);
    pthread_t serverThread;
    pthread_create(&serverThread, nullptr, OpenServer, (void*)input);
    while (!variableManager->IsConnected()) {
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
