//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_NOTEQUALTO_H
#define PROJ1_NOTEQUALTO_H


#include "ComparisonCondition.h"

class NotEqualTo : public ComparisonCondition {
public:

    bool evaluate() {
        return left->calculate() != right->calculate();
    }
};


#endif //PROJ1_NOTEQUALTO_H
