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

    string varName = node.children[0].value;
    string varValue = evaluateExpression(node.children[1]);

    // Check and store in the appropriate table
    try
    {
        intTable[varName] = stoi(varValue);
    }
    catch (...)
    {
        try
        {
            doubleTable[varName] = stod(varValue);
        }
        catch (...)
        {
            if (varValue == "True" || varValue == "False")
            {
                boolTable[varName] = (varValue == "True");
            }
            else if (varValue.length() == 1)
            {
                charTable[varName] = varValue[0];
            }
            else
            {
                stringTable[varName] = varValue;
            }
        }
    }
}

void Evaluator::evaluatePrint(const ASTNode &node)
{
    if (node.children.empty())
    {
        cerr << "Invalid print statement" << endl;
        return;
    }

    string varName = node.children[0].value;

    if (intTable.count(varName))
        cout << intTable[varName] << endl;
    else if (doubleTable.count(varName))
        cout << doubleTable[varName] << endl;
    else if (stringTable.count(varName))
        cout << stringTable[varName] << endl;
    else if (charTable.count(varName))
        cout << charTable[varName] << endl;
    else if (boolTable.count(varName))
        cout << (boolTable[varName] ? "True" : "False") << endl;
    else
        cerr << "Error: Undefined variable - " << varName << endl;
}

string Evaluator::evaluateExpression(const ASTNode &node)
{
    if (node.type == "NUMBER")
        return node.value;
    if (node.type == "STRING" || node.type == "IDENTIFIER")
        return node.value;
    if (node.type == "CHAR")
        return string(1, node.value[0]);
    if (node.type == "BOOL")
        return node.value;

    cerr << "Error: Unrecognized expression type - " << node.type << endl;
    return "";
}
