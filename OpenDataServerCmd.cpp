//
// Created by frieddv on 12/25/18.
//

#include <vector>
#include "OpenDataServerCmd.h"
#include "DataReader.h"

void OpenDataServerCmd::OpenServer(Input input) {
    DataReader dataReader;
    dataReader.connectToClient(input.portNum, input.hz, input.variableManager);
}

OpenDataServerCmd::OpenDataServerCmd(VariableManager *variableManager, IExpression *portNo, IExpression *hz)
        : variableManager(variableManager), portNo(portNo), hz(hz) {}

void OpenDataServerCmd::DoCommand() {
    Input input;
    input.portNum = (int)portNo->Calculate();
    input.hz = (int)hz->Calculate();
    input.variableManager = variableManager;
    thread server(OpenServer, input);

}
