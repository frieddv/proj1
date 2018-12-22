cmake_minimum_required(VERSION 3.12)
project(proj1)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj1 main.cpp IExpression.h BinaryExp.h UnaryExp.h ICondition.h ComparisonCondition.h AggregationCondition.h Lexer.cpp Lexer.h ICommand.h blabla.cpp DefineVarCmd.cpp VariableManager.cpp VariableManager.h)