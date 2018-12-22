//
// Created by frieddv on 12/19/18.
//

#ifndef PROJ1_VAR_H
#define PROJ1_VAR_H

#include "UnaryExp.h"
#include "VariableManager.h"

using namespace std;

class Var : public UnaryExp{
private:
    string var;
    VariableManager *manager;
public:
    Var(string varName, VariableManager *manager) : var(varName),
                                                    manager(manager){}

    double calculate() { return manager->getVarValue(var); }
};


#endif //PROJ1_VAR_H
