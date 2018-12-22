//
// Created by frieddv on 12/19/18.
//

#include <string>
#include <vector>
#include <stack>
#include "IExpression.h"
#include "UnaryExp.h"

using namespace std;

bool isNumber(string token) {

}

void ShuntingYard(vector<string> tokens) {
    stack <IExpression> values;
    stack <string> operators;
    int flag = 0;
    std::vector<string>:: iterator it = tokens.begin();
    for (; it != tokens.end(); it++) {
        if (*it == "(") {
            operators.push(*it);
            flag = 1;
        }
        else if (isNumber(*it)) {
            IExpression *exp = new Number(stoi(*it));
            values.push(*exp);
        }
        else if (isVarName(*it)) {
            //todo : fix how to see if its already in maps, means  - is it fine to add pointers to maps in this class
            IExpression *exp = new Var(*it);
            values.push(*exp);
        }
        else if (*it == ")") {
            while (!operators.empty() && operators.top() == "(") {
                IExpression &exp1 = values.top();
                values.pop();
                IExpression &exp2 = values.top();
                values.pop();

            }
        }
    }
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