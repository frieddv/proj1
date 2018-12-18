//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_ADDITION_H
#define PROJ1_ADDITION_H


#include "BinaryExp.h"

class Addition : BinaryExp {

    double calculate() {
        return left->calculate() + right->calculate();
    }
};


#endif //PROJ1_ADDITION_H
