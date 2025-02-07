#include "../../Parser.h"

/**
 * @return An AST node representing the condition
 *
 * @details
 * This function parses a condition, which is an expression enclosed in parentheses.
 * It will continue to parse tokens until it encounters a CLOSE_ROUND_BRACKET token.
 * The parsed tokens will be added as children to an AST node with the type CONDITION.
 * The node will be returned at the end of the function.
 */
ASTNode Parser::parseCondition()
{
    ASTNode condition("CONDITION");
    consume("OPEN_ROUND_BRACKET");

    while (peek().type != "CLOSE_ROUND_BRACKET")
    {
        condition.children.push_back(ASTNode(peek().type, peek().value));
        consume(peek().type);
    }

    consume("CLOSE_ROUND_BRACKET");

    return condition;
}