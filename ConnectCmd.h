//
// Created by frieddv on 12/26/18.
//

#ifndef PROJ1_CONNECTCMD_H
#define PROJ1_CONNECTCMD_H


#include "ICommand.h"
#include <vector>

struct ConnectInput {
    int portNum;
    string IP;
    VariableManager *variableManager;
};

class ConnectCmd : public ICommand {
protected:
    IExpression *port;
    string IP;
    VariableManager *variableManager;
public:

    ConnectCmd(IExpression *port, const string &IP, VariableManager *variableManager) : port(port), IP(IP),
                    variableManager(variableManager) {}

    static void* ConnectClient(void* input);

    virtual void DoCommand();
};


#endif //PROJ1_CONNECTCMD_H
