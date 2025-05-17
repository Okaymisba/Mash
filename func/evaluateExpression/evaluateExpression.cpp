#include "../../Evaluator.h"

/**
 * Evaluates an expression and returns the result as a string.
 *
 * This function evaluates an expression by checking its type and delegating
 * the evaluation to the appropriate specific evaluation function. If the
 * expression type is not recognized, a runtime error is thrown.
 *
 * @param node The root node of the expression Abstract Syntax Tree
 * @return The result of evaluating the expression as a string
 *
 * @throws runtime_error If the expression structure is invalid or
 * the expression type is unsupported
 */
string Evaluator::evaluateExpression(const ASTNode &node)
{
    if (node.type == "LONG" || node.type == "INTEGER" || node.type == "FLOAT" || node.type == "DOUBLE")
    {
        return node.value;
    }
    else if (node.type == "STRING" || node.type == "CHAR")
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
    else if (node.type == "FUNCTION_CALL")
    {
        return evaluateFunctionCall(node);
    }
    else
    {
        throw runtime_error("Unsupported expression type: " + node.type);
    }
}