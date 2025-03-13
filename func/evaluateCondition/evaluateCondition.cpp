#include "../../Evaluator.h"

/**
 * Evaluates a condition node from an abstract syntax tree (AST).
 *
 * This function processes a condition node of type "CONDITION" and evaluates
 * it based on its child nodes. It supports comparison operators such as
 * "==", "!=", ">", "<", ">=", and "<=". The function assumes that the right
 * operand can be a boolean literal ("true" or "false") or an expression that
 * needs to be evaluated. For non-boolean expressions, it converts the result
 * to a double for comparison.
 *
 * @param node The ASTNode representing the condition to be evaluated.
 * @return A string "true" or "false" depending on the evaluation result.
 * @throws runtime_error If the node type is not "CONDITION" or if an
 *                       unsupported operator is encountered.
 */

string Evaluator::evaluateCondition(const ASTNode &node)
{
    if (node.type == "CONDITION")
    {
        if (node.children[2].value == "true" || node.children[2].value == "false")
        {
            string left = evaluateExpression(node.children[0]);
            string op = node.children[1].value;
            string right = node.children[2].value;

            if (op == "==")
            {
                return (left == right) ? "true" : "false";
            }
            else if (op == "!=")
            {
                return (left != right) ? "true" : "false";
            }
            else if (op == ">")
            {
                return (left > right) ? "true" : "false";
            }
            else if (op == "<")
            {
                return (left < right) ? "true" : "false";
            }
            else if (op == ">=")
            {
                return (left >= right) ? "true" : "false";
            }
            else if (op == "<=")
            {
                return (left <= right) ? "true" : "false";
            }
            else
            {
                throw runtime_error("Unsupported condition operator: " + op);
            }
        }

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
