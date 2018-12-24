//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_COMPARISONCONDITION_H
#define PROJ1_COMPARISONCONDITION_H


#include "ICondition.h"
#include "IExpression.h"

class ComparisonCondition : public ICondition {
protected:
    IExpression *left;
    IExpression *right;

public:
    ComparisonCondition(IExpression *left, IExpression *right) : left(left), right(right) {}
    virtual bool Evaluate() = 0;
};

class EqualTo : public ComparisonCondition {
public:
    EqualTo(IExpression *left, IExpression *right) : ComparisonCondition(left, right) {}
    bool Evaluate() { return left->Calculate() == right->Calculate();}
};

class GreaterEqualThan : public ComparisonCondition{
public:
    GreaterEqualThan(IExpression *left, IExpression *right) : ComparisonCondition(left, right) {}
    bool Evaluate() { return left->Calculate() >= right->Calculate();}
};

class GreaterThan : public ComparisonCondition{
public:
    GreaterThan(IExpression *left, IExpression *right) : ComparisonCondition(left, right) {}
    bool Evaluate() { return left->Calculate() > right->Calculate();}
};

class LessEqualThan : public ComparisonCondition{
public:
    LessEqualThan(IExpression *left, IExpression *right) : ComparisonCondition(left, right) {}
    bool Evaluate() { return left->Calculate() <= right->Calculate();}
};

class LessThan : public ComparisonCondition{
public:
    LessThan(IExpression *left, IExpression *right) : ComparisonCondition(left, right) {}
    bool Evaluate() { return left->Calculate() < right->Calculate();}
};

class NotEqualTo : public ComparisonCondition {
public:
    NotEqualTo(IExpression *left, IExpression *right) : ComparisonCondition(left, right) {}
    bool Evaluate() { return left->Calculate() != right->Calculate();}
};
#endif //PROJ1_COMPARISONCONDITION_H
