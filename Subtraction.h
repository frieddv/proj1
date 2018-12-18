//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_SUBTRACTION_H
#define PROJ1_SUBTRACTION_H


#include "BinaryExp.h"

class Subtraction : BinaryExp {

    double calculate() {
        return left->calculate() - right->calculate();
    }
};


#endif //PROJ1_SUBTRACTION_H
