#include "../../Parser.h"

/**
 * Parses the right operand of an expression.
 *
 * If the next token is an open round bracket, this function parses an expression
 * enclosed in parentheses. Otherwise, it parses a term.
 *
 * @return An Abstract Syntax Tree node representing the parsed right operand.
 */

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