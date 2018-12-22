//
// Created by frieddv on 12/20/18.
//

#include "ICommand.h"

void DefineVarCmd::doCommand() {
    if (exp != nullptr) {
        manager->addLocalVar(varName, exp->calculate());
        return;
    }
    manager->bindVar(varName, bindTarget);
}