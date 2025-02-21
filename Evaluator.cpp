#include "Evaluator.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

void Evaluator::evaluate(const ASTNode &node)
{
    if (node.type == "PROGRAM")
    {
        for (const auto &child : node.children)
        {
            evaluate(child);
        }
    }
    else if (node.type == "ASSIGNMENT")
    {
        evaluateAssignment(node);
    }
    else if (node.type == "PRINT")
    {
        evaluatePrint(node);
    }
    else if (node.type == "IF STATEMENT")
    {
        evaluateIfStatement(node);
    }
    else
    {
        throw runtime_error("Unknown node type: " + node.type);
    }
}

string Evaluator::evaluateExpression(const ASTNode &node)
{
    if (node.type == "NUMBER" || node.type == "INTEGER" || node.type == "FLOAT" || node.type == "DOUBLE")
    {
        return node.value;
    }
    else if (node.type == "IDENTIFIER")
    {
        return getVariableValue(node.value);
    }
    else if (node.type == "EXPRESSION")
    {
        if (node.children.size() != 3)
        {
            throw runtime_error("Invalid expression structure.");
        }

        string left = evaluateExpression(node.children[0]);
        string op = node.children[1].value;
        string right = evaluateExpression(node.children[2]);

        return performArithmetic(left, right, op);
    }
    else
    {
        throw runtime_error("Unsupported expression type: " + node.type);
    }
}

string Evaluator::evaluateAssignment(const ASTNode &node)
{
    if (node.children.size() < 2)
    {
        throw runtime_error("Invalid assignment: expected identifier and value");
    }

    string identifier = node.children[0].value;
    string value = evaluateExpression(node.children[1]);

    if (value.find('.') != string::npos)
    {
        if (value.size() > 8)
        {
            setVariableValue(identifier, value, "DOUBLE");
        }
        else
        {
            setVariableValue(identifier, value, "FLOAT");
        }
    }
    else
    {
        setVariableValue(identifier, value, "INTEGER");
    }

    return value;
}

string Evaluator::evaluatePrint(const ASTNode &node)
{
    for (const auto &child : node.children)
    {
        string value = evaluateExpression(child);
        cout << value << endl;
    }
    return "";
}

string Evaluator::evaluateIfStatement(const ASTNode &node)
{
    if (node.children.size() < 2)
    {
        throw runtime_error("Invalid IF STATEMENT: expected condition and body");
    }

    string conditionResult = evaluateCondition(node.children[0]);
    if (conditionResult == "true")
    {
        evaluateBody(node.children[1]);
    }

    return "";
}

string Evaluator::evaluateCondition(const ASTNode &node)
{
    if (node.type == "CONDITION")
    {
        string left = evaluateExpression(node.children[0]);
        string op = node.children[1].value;
        string right = evaluateExpression(node.children[2]);

        double leftVal = stod(left);
        double rightVal = stod(right);

        if (op == "==")
        {
            return (leftVal == rightVal) ? "true" : "false";
        }
        else if (op == "!=")
        {
            return (leftVal != rightVal) ? "true" : "false";
        }
        else if (op == ">")
        {
            return (leftVal > rightVal) ? "true" : "false";
        }
        else if (op == "<")
        {
            return (leftVal < rightVal) ? "true" : "false";
        }
        else if (op == ">=")
        {
            return (leftVal >= rightVal) ? "true" : "false";
        }
        else if (op == "<=")
        {
            return (leftVal <= rightVal) ? "true" : "false";
        }
        else
        {
            throw runtime_error("Unsupported condition operator: " + op);
        }
    }
    else
    {
        throw runtime_error("Invalid condition node type: " + node.type);
    }
}

string Evaluator::evaluateBody(const ASTNode &node)
{
    if (node.type == "BODY")
    {
        for (const auto &child : node.children)
        {
            evaluate(child);
        }
    }
    else
    {
        throw runtime_error("Invalid body node type: " + node.type);
    }
    return "";
}

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

string Evaluator::getVariableValue(const string &identifier)
{
    if (intVariables.find(identifier) != intVariables.end())
    {
        return to_string(intVariables[identifier]);
    }
    else if (floatVariables.find(identifier) != floatVariables.end())
    {
        return to_string(floatVariables[identifier]);
    }
    else if (doubleVariables.find(identifier) != doubleVariables.end())
    {
        return to_string(doubleVariables[identifier]);
    }
    else if (boolVariables.find(identifier) != boolVariables.end())
    {
        return boolVariables[identifier] ? "true" : "false";
    }
    else if (stringVariables.find(identifier) != stringVariables.end())
    {
        return stringVariables[identifier];
    }
    else
    {
        throw runtime_error("Undefined variable: " + identifier);
    }
}

void Evaluator::setVariableValue(const string &identifier, const string &value, const string &type)
{
    if (type == "INTEGER")
    {
        intVariables[identifier] = stoi(value);
    }
    else if (type == "FLOAT")
    {
        floatVariables[identifier] = stof(value);
    }
    else if (type == "DOUBLE")\
    {
        doubleVariables[identifier] = stod(value);
    }
    else if (type == "BOOL")
    {
        boolVariables[identifier] = (value == "true");
    }
    else if (type == "STRING")
    {
        stringVariables[identifier] = value;
    }
    else
    {
        throw runtime_error("Unsupported variable type: " + type);
    }
}