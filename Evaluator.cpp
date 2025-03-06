#include "Evaluator.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

/**
 * Evaluates an Abstract Syntax Tree node.
 *
 * This function evaluates an Abstract Syntax Tree node by checking its type and
 * delegating the evaluation to the appropriate specific evaluation function.
 * If the node type is not recognized, a runtime error is thrown.
 */

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

/**
 * Evaluates an assignment statement by setting the value of a variable.
 *
 * This function evaluates an assignment statement by extracting the identifier
 * and value from the Abstract Syntax Tree node and setting the value of the
 * variable using the appropriate type-specific map. The variable type is
 * determined by examining the value string.
 *
 * @param node The Abstract Syntax Tree node representing the assignment statement.
 * @return An empty string.
 * @throws runtime_error If the assignment node does not have exactly two children.
 */

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

/**
 * Evaluates a print statement and outputs the result.
 *
 * This function iterates through the children of the given AST node
 * and evaluates each child based on its type. The evaluated result is printed to the standard output.
 * If an unsupported expression type is encountered, a runtime error
 * is thrown.
 *
 * @param node The Abstract Syntax Tree node representing the print statement.
 * @return An empty string.
 * @throws runtime_error If an unsupported expression type is encountered.
 */

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

void Evaluator::evaluateIfStatement(const ASTNode &node)
{
    bool conditionMet = false;

    for (const auto &child : node.children)
    {
        if (child.type == "IF" || (child.type == "ELSE IF" && !conditionMet))
        {
            if (evaluateCondition(child.children[0]) == "true")
            {
                evaluateBody(child.children[1]);
                conditionMet = true;
            }
        }
        else if (child.type == "ELSE" && !conditionMet)
        {
            evaluateBody(child.children[0]);
            conditionMet = true;
        }
    }
}
