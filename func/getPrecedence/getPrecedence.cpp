#include "../../Parser.h"

/**
 * Returns the precedence of the given operator.
 *
 * This function takes an operator string and returns a number indicating its
 * precedence. The precedence is used to determine the order of operations when
 * parsing expressions. The higher the precedence, the later the operation will
 * be evaluated.
 *
 * @param op The operator string to be evaluated.
 * @return The precedence of the given operator.
 */

int Parser::getPrecedence(const string &op)
{
    if (op == "*" || op == "/")
    {
        return 2;
    }
    if (op == "+" || op == "-")
    {
        return 1;
    }
    return 0;
}