//
// Created by frieddv on 12/19/18.
//

#ifndef PROJ1_VAR_H
#define PROJ1_VAR_H

#include <string>
#include <map>
#include "UnaryExp.h"
using namespace std;

class Var : public UnaryExp{
private:
    string var;
    map<string, string> *boundVars;
    map<string, double> *localVars;
    map<string, string> *boundToLocal;
public:
    Var(string varName, map<string, string> *boundVars, map<string, double> *localVars,
            map<string, string> *boundToLocal);

    double calculate();
};


#endif //PROJ1_VAR_H
