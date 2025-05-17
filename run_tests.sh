#!/bin/bash

g++ main.cpp Tokenizer.cpp Evaluator.cpp Parser.cpp func/readFile/readFile.cpp func/parseCondition/parseCondition.cpp func/parseBody/parseBody.cpp func/parseExpression/parseExpression.cpp func/peek/peek.cpp func/consume/consume.cpp func/parseTerm/parseTerm.cpp func/hasCorrectExtension/hasCorrectExtension.cpp func/getPrecedence/getPrecedence.cpp func/evaluateBody/evaluateBody.cpp func/evaluateCondition/evaluateCondition.cpp func/evaluateExpression/evaluateExpression.cpp func/getVariableValue/getVariableValue.cpp func/setVariableValue/setVariableValue.cpp func/performArithmetic/performArithmetic.cpp func/ValidateDataType/ValidateDataType.cpp func/parseFuncBody/parseFuncBody.cpp -o mash

function run_test() {
  FILE=$1
  EXPECTED_FILE=$2

  OUTPUT=$(./mash "$FILE")
  EXPECTED=$(<"$EXPECTED_FILE")

  if [ "$OUTPUT" == "$EXPECTED" ]; then
    echo "✅ $FILE Passed"
  else
    echo "❌ $FILE Failed"
    echo "Expected:"
    echo ""
    echo "$EXPECTED"
    echo ""
    echo "Got:"
    echo ""
    echo "$OUTPUT"
    exit 1
  fi
}

run_test tests/test1.msh tests/test1.out

echo "✅ All tests passed"
