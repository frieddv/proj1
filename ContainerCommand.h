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

    void doAllCommands() {
        for (ICommand *c : commands) {
            c->doCommand();
        }
    }
public:
    ContainerCommand(ICondition *condition) : condition(condition){}
    void addCommand(ICommand *command) {commands.push_back(command);}
    virtual void doCommand() = 0;
};

class LoopCommand : public ContainerCommand {
public:
    LoopCommand(ICondition *condition) : ContainerCommand(condition){}
    void doCommand() {
        while (condition->evaluate()) {
            doAllCommands();
        }
    }
};

class IfCommand : public ContainerCommand {
public:
    IfCommand(ICondition *condition) : ContainerCommand(condition){}
    void doCommand() {
        if (condition->evaluate()) {
            doAllCommands();
        }
    }
};

#endif //PROJ1_CONTAINERCOMMAND_H
