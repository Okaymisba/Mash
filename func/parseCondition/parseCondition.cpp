#include "../../Parser.h"

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