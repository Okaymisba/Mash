#include "../../Parser.h"
#include <stdexcept>

/**
 * Parses an arithmetic expression and returns an Abstract Syntax Tree node.
 *
 * This function parses an expression, which is a sequence of terms separated
 * by arithmetic operators. It first parses a term as the left operand, then
 * continues to parse an operator and a term as the right operand, wrapping the
 * parsed operators and operands in an AST node of type EXPRESSION. The
 * expression is parsed until it encounters a token that is not an arithmetic
 * operator, at which point it returns the parsed expression.
 *
 * @return An Abstract Syntax Tree node representing the parsed expression.
 */

ASTNode Parser::parseExpression(int minPrecedence)
{
    ASTNode left = parseTerm();

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