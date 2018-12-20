//
// Created by frieddv on 12/20/18.
//

#include "ICommand.h"

void DefineVarCmd::doCommand() {
    if (exp != nullptr) {
        (*localVars)[varName] = exp->calculate();
        return;
    }
    if (bindTarget[0] == '\"') {
        (*boundToServer)[varName] = bindTarget;
        return;
    }
    if (boundToServer->count(bindTarget)) {
        (*boundToServer)[varName] = (*boundToServer)[bindTarget];
        return;
    }
    if (boundToLocals->count(bindTarget)) {
        throw std::logic_error ("can't bind more than 2 locals parameters together");
    }
    (*boundToLocals)[varName] = bindTarget;
    (*boundToLocals)[bindTarget] = varName;
}