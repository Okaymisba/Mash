#include "../../Evaluator.h"

/**
 * Evaluates the body of an AST node by executing each child node.
 *
 * This function expects a node of type "BODY" and iterates over its children,
 * evaluating each child node using the evaluate() function. If the node is not
 * of type "BODY", a runtime error is thrown.
 *
 * @param node An ASTNode representing the body to be evaluated.
 * @return An empty string.
 * @throws runtime_error If the node type is not "BODY".
 */

string Evaluator::evaluateBody(const ASTNode &node)
{
    if (node.type == "BODY")
    {
        for (const auto &child : node.children)
        {
            evaluate(child);
        }
    }
    else
    {
        throw runtime_error("Invalid body node type: " + node.type);
    }
    return "";
}
