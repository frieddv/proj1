//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_SEGREGATIONCONDITION_H
#define PROJ1_SEGREGATIONCONDITION_H


#include "ICondition.h"

class AggregationCondition : public ICondition {
protected:

    ICondition *lhs;

    ICondition *rhs;

public:

    AggregationCondition(ICondition *left, ICondition *right) : lhs(left), rhs(right) {}

    virtual bool evaluate() = 0;
};

class OrCondition : public AggregationCondition {

    bool evaluate() {
        return lhs->evaluate() || rhs->evaluate();
    }
};

class AndCondition : public AggregationCondition {

    bool evaluate() {
        return lhs->evaluate() && rhs->evaluate();
    }
};
#endif //PROJ1_SEGREGATIONCONDITION_H
