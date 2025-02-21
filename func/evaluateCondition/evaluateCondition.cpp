#include "../../Evaluator.h"

string Evaluator::evaluateCondition(const ASTNode &node)
{
    if (node.type == "CONDITION")
    {
        string left = evaluateExpression(node.children[0]);
        string op = node.children[1].value;
        string right = evaluateExpression(node.children[2]);

        double leftVal = stod(left);
        double rightVal = stod(right);

        if (op == "==")
        {
            return (leftVal == rightVal) ? "true" : "false";
        }
        else if (op == "!=")
        {
            return (leftVal != rightVal) ? "true" : "false";
        }
        else if (op == ">")
        {
            return (leftVal > rightVal) ? "true" : "false";
        }
        else if (op == "<")
        {
            return (leftVal < rightVal) ? "true" : "false";
        }
        else if (op == ">=")
        {
            return (leftVal >= rightVal) ? "true" : "false";
        }
        else if (op == "<=")
        {
            return (leftVal <= rightVal) ? "true" : "false";
        }
        else
        {
            throw runtime_error("Unsupported condition operator: " + op);
        }
    }
    else
    {
        throw runtime_error("Invalid condition node type: " + node.type);
    }
}
