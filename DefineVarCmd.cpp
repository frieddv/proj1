//
// Created by frieddv on 12/20/18.
//

#include "ICommand.h"

void DefineVarCmd::DoCommand() {
    if (exp != nullptr) {
        manager->addLocalVar(varName, exp->Calculate());
        return;
    }
    manager->bindVar(varName, bindTarget);
}