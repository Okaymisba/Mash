#include "../../Evaluator.h"

/**
 * Evaluates a conditional expression represented by the given AST node.
 *
 * This function processes a node of type "CONDITION" by evaluating its
 * child nodes to determine the left and right operands and the operator.
 * Supported operators are "==", "!=", ">", "<", ">=", and "<=".
 * The function converts the operand values to double for comparison and
 * returns "true" or "false" as a string based on whether the condition is met.
 *
 * @param node The AST node representing the condition to evaluate.
 * @return "true" if the condition is satisfied; otherwise, "false".
 * @throws runtime_error If the node type is not "CONDITION" or the operator is unsupported.
 */

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
