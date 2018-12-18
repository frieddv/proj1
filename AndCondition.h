//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_ANDCONDITION_H
#define PROJ1_ANDCONDITION_H


#include "SegregationCondition.h"

class AndCondition : public SegregationCondition {

    bool evaluate() {
        return lhs->evaluate() && rhs->evaluate();
    }
};


#endif //PROJ1_ANDCONDITION_H
