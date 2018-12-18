//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_ANDCONDITION_H
#define PROJ1_ANDCONDITION_H


#include "AggregationCondition.h"

class AndCondition : public AggregationCondition {

    bool evaluate() {
        return lhs->evaluate() && rhs->evaluate();
    }
};


#endif //PROJ1_ANDCONDITION_H
