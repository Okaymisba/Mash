#include "../../Parser.h"
#include <stdexcept>

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

    else if (token.type == "IDENTIFIER" || token.type == "NUMBER" || token.type == "ARITHMETIC_OPERATOR" || token.type == "STRING" || token.type == "CHAR" || token.type == "BOOL")
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