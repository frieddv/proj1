//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_UNARYEXP_H
#define PROJ1_UNARYEXP_H


#include "IExpression.h"

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
#endif //PROJ1_UNARYEXP_H
