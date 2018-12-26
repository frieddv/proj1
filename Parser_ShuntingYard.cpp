//
// Created by frieddv on 12/19/18.
//

#include <string>
#include <vector>
#include "IExpression.h"
#include "BinaryExp.h"
#include "UnaryExp.h"
#include "ComparisonCondition.h"
#include "AggregationCondition.h"
#include "Parser.h"

using namespace std;

bool Parser::IsNumber(string token) {

}


SignOp Parser::WhatSign(string sign) {
    if (sign == "AND")
        return AND;
    if (sign == "OR")
        return OR;
    if (sign == ">")
        return BIGGER;
    if (sign == "<")
        return SMALLER;
    if (sign == "==")
        return EQUAL;
    if (sign == "!=")
        return NOT_EQUAL;
    if (sign == ">=")
        return BIG_EQUAL;
    if (sign == "<=")
        return SMALL_EQUAL;
    if (sign == "+")
        return PLUS;
    if (sign == "~")
        return NEG;
    if (sign == "-")
        return MINUS;
    if (sign == "*")
        return MULT;
    if (sign == "/")
        return DIV;
    return INVALID;
}

int Parser::GetPrecedence(string op) {
    if (op =="AND" || op == "OR") {
        return 1;
    }
    if (op == ">" || op == "<" || op == "==" || op == "!=" || op == ">=" || op == "<=") {
        return 2;
    }
    if (op == "+" || op == "-") {
        return 3;
    }
    if (op == "*" || op == "/") {
        return 4;
    }
    return 5;
}

IExpression* Parser::ApplyOp(string op, IExpression *left, IExpression *right) {
    switch (WhatSign(op)) {
        case AND:
            return new AndCondition(left, right);
        case OR:
            return new OrCondition(left, right);
        case SMALLER:
            return new LessThan(left, right);
        case BIGGER:
            return new GreaterThan(left, right);
        case EQUAL:
            return new EqualTo(left, right);
        case NOT_EQUAL:
            return new NotEqualTo(left, right);
        case BIG_EQUAL:
            return new GreaterEqualThan(left, right);
        case SMALL_EQUAL:
            return new LessEqualThan(left, right);
        case PLUS:
            return new Addition(left, right);
        case MINUS:
            return new Subtraction(left, right);
        case MULT:
            return new Multiplication(left, right);
        case DIV:
            return new Division(left, right);
        default:
            break;
    }
}

string Parser::ExtractStrFromStack(stack<string> stack) {
    string str = stack.top();
    stack.pop();
    return str;
}

IExpression *Parser::ExtractExpFromStack(stack<IExpression *> stack) {
    IExpression *exp = stack.top();
    stack.pop();
    return exp;
}

IExpression* Parser::ShuntingYard(queue<string> &tokens) {
    stack<IExpression*> values;
    stack<string> operators;
    int flag = 1;

    while (!tokens.empty()) {
        if (tokens.front() == "(") {
            operators.push(tokens.front());
            flag = 1;
        } else if (IsNumber(tokens.front())) {
            IExpression *exp = new Number(stoi(tokens.front()));
            values.push(exp);
            flag = 0;
        } else if (manager->doesVarExist(tokens.front())) {
            //todo : fix how to see if its already in maps, means  - is it fine to add pointers to maps in this class
            IExpression *exp = new Var(tokens.front(), manager);
            values.push(exp);
            flag = 0;
        } else if (tokens.front() == ")") {
            string temp = ExtractStrFromStack(operators);
            while (!operators.empty() && operators.top() != "(") {
                if (operators.top() == "~") {
                    IExpression *right = new Negation(ExtractExpFromStack(values));
                    values.push(right);
                    ExtractStrFromStack(operators);
                    continue;
                }
                if (GetPrecedence(temp) < GetPrecedence(operators.top())) {
                    IExpression *right = ExtractExpFromStack(values);
                    IExpression *left = ExtractExpFromStack(values);
                    IExpression *combined = ApplyOp(ExtractStrFromStack(operators), left, right);
                    values.push(combined);
                } else {
                    IExpression *right = ExtractExpFromStack(values);
                    IExpression *left = ExtractExpFromStack(values);
                    IExpression *combined = ApplyOp(temp, left, right);
                    values.push(combined);
                    temp = ExtractStrFromStack(operators);
                }
            }
            if (operators.top() == "(") {
                ExtractStrFromStack(operators);
            }
            flag = 0;
        }
        else if (tokens.front() == "-") {
            if (flag == 1) {
                operators.push("~");
            } else {
                operators.push("-");
            }
        }
        else {
            operators.push(tokens.front());
        }
        tokens.pop();
    }
    //finised passing over the Input, now making it into one big exp*
    string temp = ExtractStrFromStack(operators);
    while (values.size() != 1) {
        if (operators.top() == "~") {
            IExpression *right = new Negation(ExtractExpFromStack(values));
            values.push(right);
            ExtractStrFromStack(operators);
            continue;
        }
        if (GetPrecedence(temp) < GetPrecedence(operators.top())) {
            IExpression *right = ExtractExpFromStack(values);
            IExpression *left = ExtractExpFromStack(values);
            IExpression *combined = ApplyOp(ExtractStrFromStack(operators), left, right);
            values.push(combined);
        } else {
            IExpression *right = ExtractExpFromStack(values);
            IExpression *left = ExtractExpFromStack(values);
            IExpression *combined = ApplyOp(temp, left, right);
            values.push(combined);
            temp = ExtractStrFromStack(operators);
        }
    }
    return ExtractExpFromStack(values);
}
