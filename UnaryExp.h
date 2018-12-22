//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_UNARYEXP_H
#define PROJ1_UNARYEXP_H

#include "IExpression.h"
#include "VariableManager.h"

using namespace std;

class UnaryExp : public IExpression {
public:
    virtual double calculate() = 0;
};

class Negation : public UnaryExp {
private:
    IExpression *innerExp;
public:
    Negation(IExpression *innerExp) : innerExp(innerExp) {};
    double calculate() { return (-1 * innerExp->calculate());}
 };

class Number : public UnaryExp {
private:
    double value;
public:
    Number(double value) : value(value) {};
    double calculate() { return value;};
};

class Var : public UnaryExp{
private:
    string var;
    VariableManager *manager;
public:
    Var(string varName, VariableManager *manager) : var(varName),
                                                    manager(manager){}

    double calculate() { return manager->getVarValue(var); }
};

#endif //PROJ1_UNARYEXP_H
