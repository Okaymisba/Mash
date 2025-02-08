#include "../../Parser.h"
#include <stdexcept>

/**
 * @return An AST node representing the expression
 *
 * @details
 * This function parses an expression, which is either a literal (e.g. a number, string, etc), an expression enclosed in parentheses, or an identifier.
 * If the next token is an OPEN_ROUND_BRACKET token, it will consume the token and parse the expression inside the parentheses.
 * If the next token is not an OPEN_ROUND_BRACKET token, it will consume the token and return an AST node with the type and value of the token.
 * If an unexpected token is encountered, a runtime error will be thrown.
 */
ASTNode Parser::parseExpression()
{
    Token token = peek();

    if (token.type == "OPEN_ROUND_BRACKET")
    {
        if (token.type == "OPEN_ROUND_BRACKET")
        {
            consume("OPEN_ROUND_BRACKET");
        }

        ASTNode literal("EXPRESSION");

        while (peek().type != "CLOSE_ROUND_BRACKET")
        {
            ASTNode expression = parseExpression();
            literal.children.push_back(expression);
        }

        consume("CLOSE_ROUND_BRACKET");

        return literal;
    }

    else if (token.type == "IDENTIFIER" || token.type == "INTEGER" || token.type == "ARITHMETIC_OPERATOR" || token.type == "STRING" || token.type == "CHAR" || token.type == "BOOL" || token.type == "DOUBLE" || token.type == "FLOAT")
    {
        consume(token.type);
        ASTNode node(token.type, token.value);
        return node;
    }

    else
    {
        throw runtime_error("Syntax error: Unexpected Token: '" + token.type + "'");
    }
}