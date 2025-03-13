#include "../../Parser.h"
#include <stdexcept>

/**
 * Parses a single term in an expression and returns an Abstract Syntax Tree node.
 * A term is either a literal number (integer, float, or double) or an identifier.
 * The function will continue to parse tokens until it encounters a number or identifier.
 * If an unexpected token is encountered, a runtime error will be thrown.
 *
 * @return An Abstract Syntax Tree node representing the parsed term.
 */

ASTNode Parser::parseTerm()
{
    Token token = peek();

    if (token.type == "OPEN_ROUND_BRACKET")
    {
        consume("OPEN_ROUND_BRACKET");
        ASTNode expr = parseExpression();
        consume("CLOSE_ROUND_BRACKET");
        return expr;
    }

    if (token.type == "INTEGER" || token.type == "FLOAT" || token.type == "DOUBLE" || token.type == "STRING" || token.type == "BOOL" || token.type == "CHAR" || token.type == "LONG")
    {
        return ASTNode(token.type, consume(token.type).value);
    }
    else if (token.type == "IDENTIFIER")
    {
        return ASTNode("IDENTIFIER", consume("IDENTIFIER").value);
    }
    else
    {
        throw runtime_error("Unexpected token in expression: " + token.value);
    }
}