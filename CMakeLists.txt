cmake_minimum_required(VERSION 3.12)
project(proj1)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj1 main.cpp IExpression.h BinaryExp.h Addition.h Subtraction.h Multiplication.h Division.h UnaryExp.h Number.h ICondition.h ComparisonCondition.h EqualTo.h NotEqualTo.h GreaterEqualThan.h LessEqualThan.h GreaterThan.h LessThan.h AggregationCondition.h AndCondition.h OrCondition.h)