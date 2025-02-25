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
        evaluateIfStatement(node.children[0]);
    }
    else
    {
        throw runtime_error("Unknown node type: " + node.type);
    }
}

string Evaluator::evaluateAssignment(const ASTNode &node)
{
    if (node.children.size() < 2)
    {
        throw runtime_error("Invalid assignment: expected identifier and value");
    }

    string identifier = node.children[0].value;

    if (node.children[1].type == "STRING")
    {
        setVariableValue(identifier, node.children[1].value, "STRING");
    }
    else
    {
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
    }

    return "";
}

string Evaluator::evaluatePrint(const ASTNode &node)
{
    for (const auto &child : node.children)
    {
        if (child.type == "NUMBER" || child.type == "INTEGER" || child.type == "FLOAT" || child.type == "DOUBLE")
        {
            cout << child.value;
        }
        else if (child.type == "IDENTIFIER")
        {
            cout << getVariableValue(child.value);
        }
        else if (child.type == "EXPRESSION")
        {
            cout << evaluateExpression(child);
        }
        else if (child.type == "STRING")
        {
            cout << child.value;
        }
        else
        {
            throw runtime_error("Unsupported expression type: " + node.type);
        }
    }

    cout << endl;
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
