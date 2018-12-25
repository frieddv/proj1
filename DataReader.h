//
// Created by frieddv on 12/25/18.
//

#ifndef PROJ1_DATAREADER_H
#define PROJ1_DATAREADER_H


#include "VariableManager.h"

class DataReader {
public:
    void connectToClient(int portNumber,int hz, VariableManager *variableManager);
};


#endif //PROJ1_DATAREADER_H
