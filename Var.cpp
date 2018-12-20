//
// Created by frieddv on 12/19/18.
//

#include "Var.h"

Var::Var(string varName, map<string, string> *boundVars, map<string, double> *localVars,
         map<string, string> *boundToLocal) : boundVars(boundVars), localVars(localVars),
                                              boundToLocal(boundToLocal) {
    if (!(boundVars->count(varName)) && !(localVars->count(varName))) {
        varName = (*boundToLocal)[varName];
    }
    var = varName;
}

double Var::calculate() {
    if (localVars->count(var)) {
        return (*localVars)[var];
    }
    return (*boundVars)[var];
}


