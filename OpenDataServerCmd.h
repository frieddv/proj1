//
// Created by frieddv on 12/25/18.
//

#ifndef PROJ1_OPENDATASERVERCMD_H
#define PROJ1_OPENDATASERVERCMD_H


#include "ICommand.h"
#include <vector>
#include <pthread.h>

struct Input {
    int portNum;
    int hz;
    VariableManager *variableManager;
};

class OpenDataServerCmd : public ICommand{
protected:
    VariableManager *variableManager;
    IExpression *portNo;
    IExpression *hz;
public:

    OpenDataServerCmd(VariableManager *variableManager, IExpression *portNo, IExpression *hz);

    static void* OpenServer(void* input);

    virtual void DoCommand();
};


#endif //PROJ1_OPENDATASERVERCMD_H
