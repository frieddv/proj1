//
// Created by frieddv on 12/19/18.
//

#include <string>
#include <vector>
#include <stack>
#include "IExpression.h"

using namespace std;

void ShuntingYard(vector<string> tokens) {
    stack <double> values;
    stack <string> operators;

}

int precedence (string op) {
    if (!(op.compare("AND")) || !(op.compare("OR"))) {
        return 1;
    }
    if (!(op.compare(">")) || !(op.compare("<")) ||
    !(op.compare("==")) || !(op.compare("!=")) || !(op.compare(">=")) || !(op.compare("<="))) {
        return 2;
    }
    if (!(op.compare("+")) || !(op.compare("-"))) {
        return 3;
    }
    if (!(op.compare("*")) || !(op.compare("/"))) {
        return 4;
    }
    return 0;
}

IExpression *apllOp () {

}