#include "../../Parser.h"

ASTNode Parser::parseBody()
{
    while (peek().type == "LINE_BREAK")
    {
        consume("LINE_BREAK");
    }

    consume("OPEN_CURLY_BRACKET");
    ASTNode body("BODY");

    while (peek().type != "CLOSE_CURLY_BRACKET")
    {
        if (peek().type == "LINE_BREAK")
        {
            consume("LINE_BREAK");
        }
        else
        {
            ASTNode statement = parseStatement();
            body.children.push_back(statement);
        }
    }

    consume("CLOSE_CURLY_BRACKET");

    return body;
}
