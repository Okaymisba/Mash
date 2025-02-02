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

        body.children.push_back(ASTNode(peek().type, peek().value));
        consume(peek().type);
    }

    consume("CLOSE_CURLY_BRACKET");

    return body;
}
