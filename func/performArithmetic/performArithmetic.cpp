#include "../../Evaluator.h"

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