cmake_minimum_required(VERSION 3.10)
project(Mash)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(func/hasCorrectExtension)
include_directories(func/readFile)
include_directories(structs)

add_executable(Mash
        func/consume/consume.cpp
        func/evaluateBody/evaluateBody.cpp
        func/evaluateCondition/evaluateCondition.cpp
        func/evaluateExpression/evaluateExpression.cpp
        func/getInput/getInput.cpp
        func/getPrecedence/getPrecedence.cpp
        func/getVariableValue/getVariableValue.cpp
        func/hasCorrectExtension/hasCorrectExtension.cpp
        func/hasCorrectExtension/hasCorrectExtension.h
        func/parseBody/parseBody.cpp
        func/parseCondition/parseCondition.cpp
        func/parseExpression/parseExpression.cpp
        func/parseFuncBody/parseFuncBody.cpp
        func/parseInput/parseInput.cpp
        func/parseTerm/parseTerm.cpp
        func/peek/peek.cpp
        func/performArithmetic/performArithmetic.cpp
        func/readFile/readFile.cpp
        func/readFile/readFile.h
        func/setVariableValue/setVariableValue.cpp
        func/ValidateDataType/ValidateDataType.cpp
        structs/ASTNode.h
        structs/Token.h
        Evaluator.cpp
        Evaluator.h
        main.cpp
        Parser.cpp
        Parser.h
        Tokenizer.cpp
        Tokenizer.h)
