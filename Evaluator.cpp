#include "Evaluator.h"

void Evaluator::evaluate(const ASTNode &node)
{
    if (node.type == "ASSIGNMENT")
    {
        handleAssignment(node);
    }
    else if (node.type == "PRINT")
    {
        handlePrint(node);
    }
    else
    {
        for (const auto &child : node.children)
        {
            evaluate(child);
        }
    }
}

void Evaluator::handleAssignment(const ASTNode &node)
{
    if (node.children.size() < 2)
    {
        throw runtime_error("Invalid assignment statement.");
    }

    string varName = node.children[0].value;
    ASTNode expressionNode = node.children[1];

    if (expressionNode.type == "INTEGER")
    {
        intVariables[varName] = stoi(expressionNode.value);
    }
    else if (expressionNode.type == "FLOAT")
    {
        floatVariables[varName] = stod(expressionNode.value);
    }
    else if (expressionNode.type == "STRING")
    {
        stringVariables[varName] = expressionNode.value;
    }
    else if (expressionNode.type == "BOOL")
    {
        boolVariables[varName] = (expressionNode.value == "True");
    }
    else if (expressionNode.type == "ARITHMETIC_OPERATOR")
    {
        int result = evaluateIntegerExpression(expressionNode);
        intVariables[varName] = result;
    }
    else
    {
        throw runtime_error("Unsupported assignment type.");
    }
}

void Evaluator::handlePrint(const ASTNode &node)
{
    if (node.children.empty())
    {
        throw runtime_error("Print statement has no argument.");
    }

    ASTNode expressionNode = node.children[0];

    if (expressionNode.type == "INTEGER")
    {
        cout << stoi(expressionNode.value) << endl;
    }
    else if (expressionNode.type == "FLOAT")
    {
        cout << stod(expressionNode.value) << endl;
    }
    else if (expressionNode.type == "STRING")
    {
        cout << expressionNode.value << endl;
    }
    else if (expressionNode.type == "BOOL")
    {
        cout << (expressionNode.value == "True" ? "True" : "False") << endl;
    }
    else if (expressionNode.type == "ARITHMETIC_OPERATOR")
    {
        cout << evaluateIntegerExpression(expressionNode) << endl;
    }
    else
    {
        throw runtime_error("Unsupported print statement.");
    }
}

int Evaluator::evaluateIntegerExpression(const ASTNode &node)
{
    if (node.type == "INTEGER")
    {
        return stoi(node.value);
    }
    if (node.children.size() == 2)
    {
        int left = evaluateIntegerExpression(node.children[0]);
        int right = evaluateIntegerExpression(node.children[1]);

        if (node.type == "ARITHMETIC_OPERATOR")
        {
            string op = node.value;
            if (op == "+")
                return left + right;
            if (op == "-")
                return left - right;
            if (op == "*")
                return left * right;
            if (op == "/")
            {
                if (right == 0)
                    throw runtime_error("Division by zero.");
                return left / right;
            }
            if (op == "%")
                return left % right;
        }
    }
    throw runtime_error("Invalid arithmetic expression.");
}

double Evaluator::evaluateFloatExpression(const ASTNode &node)
{
    if (node.type == "FLOAT")
    {
        return stod(node.value);
    }
    throw runtime_error("Invalid float expression.");
}

string Evaluator::evaluateStringExpression(const ASTNode &node)
{
    if (node.type == "STRING")
    {
        return node.value;
    }
    throw runtime_error("Invalid string expression.");
}

bool Evaluator::evaluateBooleanExpression(const ASTNode &node)
{
    if (node.type == "BOOL")
    {
        return node.value == "True";
    }
    throw runtime_error("Invalid boolean expression.");
}
