//
// Created by frieddv on 12/19/18.
//

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "IExpression.h"
#include "BinaryExp.h"
#include "UnaryExp.h"

typedef enum {AND, OR, BIGGER, SMALLER, EQUAL, NOTEQUAL, BIGEQUAL, SMALLEQUAL, PLUS, MINUS, MULT, DIV} signOp;

using namespace std;

bool isNumber(string token) {

}

signOp whatSign (string sign) {
    if (!sign.compare("AND"))
        return AND;
    if (!sign.compare("OR"))
        return OR;
    if (!sign.compare(">"))
        return BIGGER;
    if (!sign.compare("<"))
        return SMALLER;
    if (!sign.compare("=="))
        return EQUAL;
    if (!sign.compare("!="))
        return NOTEQUAL;
    if (!sign.compare(">="))
        return BIGEQUAL;
    if (!sign.compare("<="))
        return SMALLEQUAL;
    if (!sign.compare("+"))
        return PLUS;
    if (!sign.compare("-"))
        return MINUS;
    if (!sign.compare("*"))
        return MULT;
    if (!sign.compare("/"))
        return DIV;
}

int Precedence (string op) {
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
    return 5;
}

void ShuntingYard(queue<string> tokens) {
    bool twoExpressions;
    stack <IExpression*> values;
    stack <string> operators;
    int flag = 0;

    while (!tokens.empty()) {
        if (tokens.front() == "(") {
            operators.push(tokens.front());
            flag = 1;
        }
        else if (isNumber(tokens.front())) {
            IExpression *exp = new Number(stoi(tokens.front()));
            values.push(exp);
            flag = 0;
        }
        else if (isVarName(tokens.front())) {
            //todo : fix how to see if its already in maps, means  - is it fine to add pointers to maps in this class
            
            IExpression *exp = new Var(tokens.front());
            values.push(exp);
            flag = 0;
        }
        else if (tokens.front() == ")") {
            string temp = operators.top();
            operators.pop();
            while (!operators.empty() && operators.top() != "(") {
                if (Precedence(temp) < Precedence(operators.top())) {
                    IExpression *right = values.top();
                    values.pop();
                    IExpression *left = values.top();
                    values.pop();
                    IExpression *combined;
                    switch (whatSign(operators.top())) {
                        case AND:
                            break;
                        case OR:
                            break;
                        case SMALLER:
                            twoExpressions = left < right;
                            break;
                        case BIGGER:
                            twoExpressions = left > right;
                            break;
                        case EQUAL:
                            twoExpressions = left == right;
                            break;
                            //todo checking if needed to get rid from those cases.
//                        case PLUS:
//                            *combined = new Addition(left, right);
//                            values.push(combined);
//                            operators.pop();
//                            break;
//                        case MINUS:
//                            *combined = new Subtraction(left, right);
//                            values.push(combined);
//                            operators.pop();
//                            break;
                        case MULT:
                            *combined = new Multiplication(left, right);
                            values.push(combined);
                            operators.pop();
                            break;
                        case DIV:
                            *combined = new Division(left, right);
                            values.push(combined);
                            operators.pop();
                            break;
                        default:
                            break;
                    }
                }
                else {
                    IExpression *right = values.top();
                    values.pop();
                    IExpression *left = values.top();
                    values.pop();
                    IExpression *combined;
                    switch (whatSign(temp)) {
                        case AND:
                            break;
                        case OR:
                            break;
                        case SMALLER:
                            twoExpressions = left < right;
                            break;
                        case BIGGER:
                            twoExpressions = left > right;
                            break;
                        case EQUAL:
                            twoExpressions = left == right;
                            break;
                            //todo checking if needed to get rid from those cases.
//                        case PLUS:
//                            *combined = new Addition(left, right);
//                            values.push(combined);
//                            temp = operators.top();
//                            operators.pop();
//                            break;
//                        case MINUS:
//                            *combined = new Subtraction(left, right);
//                            values.push(combined);
//                            temp = operators.top();
//                            operators.pop();
//                            break;
                        case MULT:
                            *combined = new Multiplication(left, right);
                            values.push(combined);
                            temp = operators.top();
                            operators.pop();
                            break;
                        case DIV:
                            *combined = new Division(left, right);
                            values.push(combined);
                            temp = operators.top();
                            operators.pop();
                            break;
                        default:
                            break;
                }
            }

        }
    }
    else if ()
}

IExpression *apllOp () {

}