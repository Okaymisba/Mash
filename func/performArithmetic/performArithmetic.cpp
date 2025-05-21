#include "../../Evaluator.h"

/**
 * Performs an arithmetic operation on the given left and right operands with
 * the specified operator.
 *
 * This function takes two strings representing the left and right operands,
 * and a string representing the arithmetic operator to be performed.
 * Supported operators are "+", "-", "*", "/", and "%".
 * The function converts the operand values to double, performs the arithmetic
 * operation, and returns the result as a string. If the result is an integer,
 * it is returned as an integer string; otherwise, it is returned as a decimal
 * string.
 *
 * @param left The left operand as a string.
 * @param right The right operand as a string.
 * @param op The arithmetic operator to be performed as a string.
 * @return The result of the arithmetic operation as a string.
 * @throws runtime_error If the operator is unsupported or if division by zero is attempted.
 */

string Evaluator::performArithmetic(const string &left, const string &right, const string &op)
{

    double leftVal = stod(left);
    double rightVal = stod(right);
    double result = 0;

    if (op == "+")
    {
        result = leftVal + rightVal;
    }
    else if (op == "-")
    {
        result = leftVal - rightVal;
    }
    else if (op == "*")
    {
        result = leftVal * rightVal;
    }
    else if (op == "/")
    {
        if (rightVal == 0)
        {
            throw runtime_error("Division by zero");
        }
        result = leftVal / rightVal;
    }
    else if (op == "%")
    {
        result = static_cast<int>(leftVal) % static_cast<int>(rightVal);
    }
    else
    {
        throw runtime_error("Unsupported arithmetic operator: " + op);
    }

    if (result == static_cast<int>(result))
        return to_string(static_cast<int>(result));

    return to_string(result);
}