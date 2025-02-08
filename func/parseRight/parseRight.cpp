#include "../../Parser.h"

ASTNode Parser::parseRight()
{
    if (peek().type == "OPEN_ROUND_BRACKET")
    {
        consume("OPEN_ROUND_BRACKET");
        ASTNode expression = parseExpression();
        consume("CLOSE_ROUND_BRACKET");
        return expression;
    }
    else
    {
        return parseTerm();
    }
}