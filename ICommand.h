//
// Created by frieddv on 12/18/18.
//

#ifndef PROJ1_ICOMMAND_H
#define PROJ1_ICOMMAND_H


#include <iostream>
#include <chrono>
#include <thread>
#include "ICondition.h"
#include "IExpression.h"
#include "VariableManager.h"

using namespace std;

class ICommand {
public:
    virtual void DoCommand() = 0;
    virtual ~ICommand() = default;
};

class PrintExpCmd : public ICommand {
private:
    IExpression *exp;
public:
    PrintExpCmd(IExpression *exp) : exp(exp) {};
    void DoCommand() { cout << exp->Calculate() << endl;}
    virtual ~PrintExpCmd() { delete exp; }
};

class PrintStrCmd : public ICommand {
private:
    string str;
public:
    PrintStrCmd(string str) {this->str = str.substr(1, str.length() - 2);}
    void DoCommand() {cout << str << endl;}
};

class SleepCmd : public ICommand {
private:
    IExpression *exp;
public:
    SleepCmd(IExpression *exp) : exp(exp) {}
    void DoCommand() { this_thread::sleep_for(chrono::milliseconds((int)exp->Calculate())); }
    virtual ~SleepCmd() { delete exp; }
};

class DefineVarCmd : public ICommand {
private:
    VariableManager *manager;
    string varName;
    string bindTarget;
    IExpression *exp;
public:
    DefineVarCmd(VariableManager *manager, const string &varName, const string &bindTarget) : manager(manager),
                    varName(varName), bindTarget(bindTarget), exp(nullptr) {}

    DefineVarCmd(VariableManager *manager, const string &varName, IExpression *exp) : manager(manager),
                    varName(varName), exp(exp) {}
    void DoCommand();
    virtual ~DefineVarCmd() {
        if (exp != nullptr)
            delete exp;
    }
};

class UpdateVarCmd : public ICommand {
private:
    VariableManager *manager;
    string varName;
    IExpression *exp;
public:
    UpdateVarCmd(VariableManager *manager, const string &varName, IExpression *exp) : manager(manager),
                    varName(varName), exp(exp) {}
    void DoCommand() { manager->SetVarValue(varName, exp->Calculate()); }
    virtual ~UpdateVarCmd() { delete exp; }
};
#endif //PROJ1_ICOMMAND_H
