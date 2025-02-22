#include "../../Evaluator.h"

string Evaluator::evaluateExpression(const ASTNode &node)
{
    if (node.type == "NUMBER" || node.type == "INTEGER" || node.type == "FLOAT" || node.type == "DOUBLE")
    {
        return node.value;
    }
    else if (node.type == "IDENTIFIER")
    {
        return getVariableValue(node.value);
    }
    else if (node.type == "EXPRESSION")
    {
        if (node.children.size() != 3)
        {
            throw runtime_error("Invalid expression structure.");
        }

        string left = evaluateExpression(node.children[0]);
        string op = node.children[1].value;
        string right = evaluateExpression(node.children[2]);

        return performArithmetic(left, right, op);
    }
    else
    {
        throw runtime_error("Unsupported expression type: " + node.type);
    }
}