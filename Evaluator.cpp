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
    else if (node.type == "WHILE")
    {
        evaluateWhileLoop(node);
    }
    else if (node.type == "FOR")
    {
        evaluateForLoop(node);
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
    else if (node.children[1].type == "CHAR")
    {
        setVariableValue(identifier, node.children[1].value, "CHAR");
    }
    else if (node.children[1].type == "BOOL")
    {
        setVariableValue(identifier, node.children[1].value, "BOOL");
    }
    else if (node.children[1].type == "DOUBLE")
    {
        setVariableValue(identifier, node.children[1].value, "DOUBLE");
    }
    else if (node.children[1].type == "FLOAT")
    {
        setVariableValue(identifier, node.children[1].value, "FLOAT");
    }
    else if (node.children[1].type == "LONG")
    {
        setVariableValue(identifier, node.children[1].value, "LONG");
    }
    else if (node.children[1].type == "INTEGER")
    {
        setVariableValue(identifier, node.children[1].value, "INTEGER");
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
        else if (value.size() >= 10)
        {
            setVariableValue(identifier, value, "LONG");
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

/**
 * Evaluates an if statement by checking conditions and executing bodies.
 *
 * This function iterates over the children of the given AST node and evaluates
 * the condition and body of each if and else if clause. If the condition is
 * satisfied, the body is executed and the function returns. If none of the
 * conditions are satisfied, the else clause is executed if present.
 *
 * @param node The Abstract Syntax Tree node representing the if statement.
 */

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

/**
 * Evaluates a while loop statement by checking the condition and executing the body.
 *
 * This function evaluates the condition of the given while loop node and executes
 * the body if the condition is satisfied. The condition is evaluated using the
 * evaluateCondition() function, and the body is evaluated using the evaluateBody()
 * function. The process is repeated until the condition is no longer satisfied.
 *
 * @param node The Abstract Syntax Tree node representing the while loop statement.
 */

void Evaluator::evaluateWhileLoop(const ASTNode &node)
{
    while (evaluateCondition(node.children[0]) == "true")
    {
        evaluateBody(node.children[1]);
    }
}

/**
 * Evaluates a for loop statement by initializing the loop variable and iterating through the range.
 *
 * This function evaluates a for loop by:
 * 1. Getting the loop variable identifier
 * 2. Extracting the range information (start, type, end)
 * 3. Optionally getting the step value
 * 4. Executing the loop body for each value in the range
 *
 * @param node The Abstract Syntax Tree node representing the for loop statement.
 */

void Evaluator::evaluateForLoop(const ASTNode &node)
{
    string identifier = node.children[0].value;

    const ASTNode &rangeNode = node.children[1];

    string startValue = evaluateExpression(rangeNode.children[0].children[0]);
    int start = stoi(startValue);

    string rangeType = rangeNode.children[1].type;

    string endValue = evaluateExpression(rangeNode.children[2].children[0]);
    int end = stoi(endValue);

    int step = 1;
    if (node.children.size() > 3)
    {
        string stepValue = evaluateExpression(node.children[2].children[0]);
        step = stoi(stepValue);
    }

    const ASTNode &body = node.children.back();

    if (rangeType == "TO")
    {
        for (int i = start; i <= end; i += step)
        {
            setVariableValue(identifier, to_string(i), "INTEGER");
            evaluateBody(body);
        }
    }
    else if (rangeType == "DOWNTO")
    {
        for (int i = start; i >= end; i -= step)
        {
            setVariableValue(identifier, to_string(i), "INTEGER");
            evaluateBody(body);
        }
    }
    else if (rangeType == "UNTIL")
    {
        for (int i = start; i < end; i += step)
        {
            setVariableValue(identifier, to_string(i), "INTEGER");
            evaluateBody(body);
        }
    }
    else if (rangeType == "DOWNUNTIL")
    {
        for (int i = start; i > end; i -= step)
        {
            setVariableValue(identifier, to_string(i), "INTEGER");
            evaluateBody(body);
        }
    }
    else
    {
        throw runtime_error("Invalid range type in for loop: " + rangeType);
    }
}
