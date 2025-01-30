#include "Evaluator.h"

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
    else
    {
        cerr << "Unknown node type: " << node.type << endl;
    }
}

void Evaluator::evaluateAssignment(const ASTNode &node)
{
    if (node.children.size() < 2)
    {
        cerr << "Invalid assignment statement" << endl;
        return;
    }

    string varName = node.children[0].value; // Identifier
    string varValue = node.children[1].value; // Assigned value

    symbolTable[varName] = varValue;
}

void Evaluator::evaluatePrint(const ASTNode &node)
{
    if (node.children.empty())
    {
        cerr << "Invalid print statement" << endl;
        return;
    }

    string value = node.children[0].value;

    if (symbolTable.find(value) != symbolTable.end())
    {
        cout << symbolTable[value] << endl;
    }
    else
    {
        cout << value << endl;
    }
}
