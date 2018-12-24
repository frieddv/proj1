//
// Created by ariel on 12/24/18.
//

#ifndef PROJ1_CONTAINERCOMMAND_H
#define PROJ1_CONTAINERCOMMAND_H

#include <list>
#include "ICommand.h"

class ContainerCommand : public ICommand {
protected:
    ICondition *condition;
    list<ICommand*> commands;

    void DoAllCommands() {
        for (ICommand *c : commands) {
            c->DoCommand();
        }
    }
public:
    ContainerCommand(ICondition *condition) : condition(condition){}
    void AddCommand(ICommand *command) {commands.push_back(command);}
    virtual void DoCommand() = 0;
};

class LoopCommand : public ContainerCommand {
public:
    LoopCommand(ICondition *condition) : ContainerCommand(condition){}
    void DoCommand() {
        while (condition->Evaluate()) {
            DoAllCommands();
        }
    }
};

class IfCommand : public ContainerCommand {
public:
    IfCommand(ICondition *condition) : ContainerCommand(condition){}
    void DoCommand() {
        if (condition->Evaluate()) {
            DoAllCommands();
        }
    }
};

#endif //PROJ1_CONTAINERCOMMAND_H
