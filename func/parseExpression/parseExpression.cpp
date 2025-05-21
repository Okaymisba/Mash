#include "../../Parser.h"
#include <stdexcept>

/**
 * Parses an expression and returns an Abstract Syntax Tree node.
 *
 * This function parses an expression from the token stream, using the
 * precedence climbing algorithm to handle operator precedence.
 * The function takes an optional minimum precedence argument, which
 * is used to determine when to stop parsing.
 *
 * @param minPrecedence The minimum precedence to parse, defaulting to 0.
 * @return An Abstract Syntax Tree node representing the parsed expression.
 */
ASTNode Parser::parseExpression(int minPrecedence)
{
    ASTNode left;

    if (peek().type == "IDENTIFIER" && currentIndex + 1 < tokens.size() && tokens[currentIndex + 1].type == "OPEN_ROUND_BRACKET")
    {
        left = parseFunctionCall();
    }
    else if (peek().type == "INPUT")
    {
        left = parseInput();
    }
    else
    {
        left = parseTerm();
    }

    while (true)
    {
        Token opToken = peek();
        string op = opToken.value;
        int precedence = getPrecedence(op);

        if (opToken.type != "ARITHMETIC_OPERATOR" || precedence < minPrecedence)
        {
            break;
        }

        consume("ARITHMETIC_OPERATOR");

        ASTNode right = parseExpression(precedence + 1);

        ASTNode expr("EXPRESSION");
        expr.children.push_back(left);
        expr.children.push_back(ASTNode("ARITHMETIC_OPERATOR", op));
        expr.children.push_back(right);

        left = expr;
    }

    return left;
}