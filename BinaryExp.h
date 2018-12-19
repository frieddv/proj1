//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_BINARYEXP_H
#define PROJ1_BINARYEXP_H

#include <stdexcept>
#include "IExpression.h"

class BinaryExp : public IExpression {
protected:
    IExpression *left;
    IExpression *right;

public:

    virtual double calculate() = 0;

    BinaryExp(IExpression *a, IExpression *b) : left(a), right(b) {};
};
class Addition : public BinaryExp {
    double calculate() { return left->calculate() + right->calculate();}
};
class Subtraction : public BinaryExp {
    double calculate() { return left->calculate() - right->calculate();}
};
class Multiplication : public BinaryExp {
    double calculate() { return left->calculate() * right->calculate();}
};
class Division : public BinaryExp {
    double calculate() {
        if (right->calculate() == 0) {
            throw std::logic_error("Divide by zero exception");
        }
        return left->calculate() / right->calculate();
    }
};
#endif //PROJ1_BINARYEXP_H
