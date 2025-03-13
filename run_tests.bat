@echo off
setlocal enabledelayedexpansion

g++ main.cpp Tokenizer.cpp Evaluator.cpp Parser.cpp func/readFile/readFile.cpp func/parseCondition/parseCondition.cpp func/parseBody/parseBody.cpp func/parseExpression/parseExpression.cpp func/peek/peek.cpp func/consume/consume.cpp func/parseTerm/parseTerm.cpp func/hasCorrectExtension/hasCorrectExtension.cpp func/getPrecedence/getPrecedence.cpp func/evaluateBody/evaluateBody.cpp func/evaluateCondition/evaluateCondition.cpp func/evaluateExpression/evaluateExpression.cpp func/getVariableValue/getVariableValue.cpp func/setVariableValue/setVariableValue.cpp func/performArithmetic/performArithmetic.cpp -o mash

set "file=tests\test1.msh"
set "expected_file=tests\test1.out"

set "output="
for /f "usebackq delims=" %%a in (`./mash %file%`) do (
    set "line=%%a"
    if defined output (
        set "output=!output!!line!!nl!"
    ) else (
        set "output=!line!"
    )
)

set "expected="
for /f "usebackq delims=" %%a in (%expected_file%) do (
    set "line=%%a"
    if defined expected (
        set "expected=!expected!!line!!nl!"
    ) else (
        set "expected=!line!"
    )
)

if "!output!"=="!expected!" (
    echo ✅ %file% Passed
) else (
    echo ❌ %file% Failed
    echo Expected:
    type %expected_file%
    echo Got:
    ./mash %file%
    exit /b 1
)

echo ✅ All tests passed
