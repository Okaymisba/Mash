#include "../../Parser.h"


/**
 * Parses a body of statements and returns an Abstract Syntax Tree node.
 *
 * This function parses a body of statements, which consists of a block of statements
 * enclosed within curly brackets. It constructs an AST node with the type "BODY"
 * and adds the parsed statements as its children. The function continues to parse
 * tokens until it encounters a closing curly bracket.
 *
 * @return An Abstract Syntax Tree node representing the body of statements.
 */
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

    while (peek().type == "LINE_BREAK")
    {
        consume("LINE_BREAK");
    }

    return body;
}