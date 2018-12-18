//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_ORCONDITION_H
#define PROJ1_ORCONDITION_H


#include "SegregationCondition.h"

class OrCondition : public SegregationCondition {

    bool evaluate() {
        return lhs->evaluate() || rhs->evaluate();
    }
};


#endif //PROJ1_ORCONDITION_H
