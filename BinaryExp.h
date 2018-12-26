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

    virtual double Calculate() = 0;
    BinaryExp(IExpression *a, IExpression *b) : left(a), right(b) {}
    virtual ~BinaryExp() {
        delete left;
        delete right;
    }
};

class Addition : public BinaryExp {
public:
    Addition(IExpression *a, IExpression *b) : BinaryExp(a, b) {}
    double Calculate() { return left->Calculate() + right->Calculate();}
    virtual ~Addition(){}
};

class Subtraction : public BinaryExp {
public:
    Subtraction(IExpression *a, IExpression *b) : BinaryExp(a, b) {}
    double Calculate() { return left->Calculate() - right->Calculate();}
    virtual ~Subtraction() {}
};

class Multiplication : public BinaryExp {
public:
    Multiplication(IExpression *a, IExpression *b) : BinaryExp(a, b) {}
    double Calculate() { return left->Calculate() * right->Calculate();}
    virtual ~Multiplication() {}
};

class Division : public BinaryExp {
public:
    Division(IExpression *a, IExpression *b) : BinaryExp(a, b) {}
    double Calculate() {
        if (right->Calculate() == 0) {
            throw std::logic_error("Divide by zero exception");
        }
        return left->Calculate() / right->Calculate();
    }
    virtual ~Division() {}
};
#endif //PROJ1_BINARYEXP_H
