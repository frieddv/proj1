//
// Created by frieddv on 12/20/18.
//

#include "ICommand.h"

void DefineVarCmd::DoCommand() {
    if (exp != nullptr) {
        manager->AddLocalVar(varName, exp->Calculate());
        return;
    }
    manager->BindVar(varName, bindTarget);
}