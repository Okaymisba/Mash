#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "structs/ASTNode.h"
#include <string>
#include <map>
#include <stdexcept>
#include <regex> // Include regex for type checking

using namespace std;

class Evaluator
{
public:
    void evaluate(const ASTNode &node);
    void evaluateFunctionCall(const ASTNode &node);

private:
    map<string, int> intVariables;
    map<string, long> longVariables;
    map<string, float> floatVariables;
    map<string, double> doubleVariables;
    map<string, bool> boolVariables;
    map<string, string> stringVariables;
    map<string, char> charVariables;

    map<string, ASTNode> functions; // Map to store function definitions
    map<string, string> variables;  // Map to store local variables

    string evaluateExpression(const ASTNode &node);
    string evaluateAssignment(const ASTNode &node);
    string evaluatePrint(const ASTNode &node);
    void evaluateIfStatement(const ASTNode &node);
    void evaluateWhileLoop(const ASTNode &node);
    void evaluateForLoop(const ASTNode &node);
    string evaluateCondition(const ASTNode &node);
    string evaluateBody(const ASTNode &node);

    string performArithmetic(const string &left, const string &right, const string &op);
    string getVariableValue(const string &identifier);
    void setVariableValue(const string &identifier, const string &value, const string &type);

    // Add helper functions for type checking
    bool isInteger(const string &value);
    bool isFloat(const string &value);
    bool isBool(const string &value);   // Add this declaration
    bool isChar(const string &value);   // Add this declaration
    bool isString(const string &value); // Add this declaration
    bool isLong(const string &value);   // Add this declaration
    bool isDouble(const string &value); // Add this declaration
};

#endif