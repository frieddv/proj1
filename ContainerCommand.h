//
// Created by ariel on 12/24/18.
//

#ifndef PROJ1_CONTAINERCOMMAND_H
#define PROJ1_CONTAINERCOMMAND_H

#include <list>
#include "ICommand.h"

class ContainerCommand : public ICommand {
protected:
    IExpression *expression;
    queue<ICommand*> commands;

    void DoAllCommands() {
        queue<ICommand*> copy(commands);
        while (!copy.empty()) {
            ICommand *c = copy.front();
            copy.pop();
            c->DoCommand();
        }
    }
public:
    ContainerCommand(IExpression *expression) : expression(expression){}

    void AddCommand(ICommand *command) {commands.push(command);}

    virtual void DoCommand() = 0;

    virtual ~ContainerCommand() {
        while (!commands.empty()) {
            ICommand *c = commands.front();
            commands.pop();
            delete c;
        }
    }
};

class LoopCommand : public ContainerCommand {
public:
    LoopCommand(IExpression *expression) : ContainerCommand(expression){}
    void DoCommand() {
        while (expression->Calculate()) {
            DoAllCommands();
        }
    }
};

class IfCommand : public ContainerCommand {
public:
    IfCommand(IExpression *expression) : ContainerCommand(expression){}
    void DoCommand() {
        if (expression->Calculate()) {
            DoAllCommands();
        }
    }
};

#endif //PROJ1_CONTAINERCOMMAND_H
