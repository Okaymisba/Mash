#include "../../Evaluator.h"
#include <iostream>

string Evaluator::evaluateExpressionForPrint(const ASTNode &node)
{
    string result = evaluateExpression(node);
    return result;
}