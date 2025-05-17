#include "../../Evaluator.h"

/**
 * Evaluates the body of an AST node by executing each child node.
 *
 * This function expects a node of type "BODY" or "FUNC_BODY" and iterates over its children,
 * evaluating each child node using the evaluate() function. If a child node is a return statement,
 * the return value is extracted and a ReturnException is thrown with the return value.
 * If the node is not of type "BODY" or "FUNC_BODY", a runtime error is thrown.
 *
 * @param node An ASTNode representing the body to be evaluated.
 * @return An empty string.
 * @throws runtime_error If the node type is not "BODY" or "FUNC_BODY".
 * @throws ReturnException If a return statement is encountered.
 */
string Evaluator::evaluateBody(const ASTNode &node)
{
    if (node.type == "BODY" || node.type == "FUNC_BODY")
    {
        for (const auto &child : node.children)
        {
            if (child.type == "RETURN")
            {
                string returnValue = evaluateExpression(child.children[0]);
                throw ReturnException(returnValue);
            }
            else
            {
                evaluate(child);
            }
        }
    }
    else
    {
        throw runtime_error("Invalid body node type: " + node.type);
    }
    return "";
}
