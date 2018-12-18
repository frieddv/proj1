//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_MULTIPLICATION_H
#define PROJ1_MULTIPLICATION_H


#include "BinaryExp.h"

class Multiplication : BinaryExp {

    double calculate() {
        return left->calculate() * right->calculate();
    }
};


#endif //PROJ1_MULTIPLICATION_H
