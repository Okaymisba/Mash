#include "../../Evaluator.h"

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
