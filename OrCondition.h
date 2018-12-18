//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_ORCONDITION_H
#define PROJ1_ORCONDITION_H


#include "AggregationCondition.h"

class OrCondition : public AggregationCondition {

    bool evaluate() {
        return lhs->evaluate() || rhs->evaluate();
    }
};


#endif //PROJ1_ORCONDITION_H
