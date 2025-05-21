#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "structs/ASTNode.h"
#include <string>
#include <map>
#include <stdexcept>
#include <regex> // Include regex for type checking

using namespace std;
#include <exception>
#include <string>

class ReturnException : public std::exception
{
private:
    std::string returnValue;

public:
    explicit ReturnException(const std::string &value) : returnValue(value) {}

    const char *what() const noexcept override
    {
        return "ReturnException";
    }

    std::string value() const
    {
        return returnValue;
    }
};
class Evaluator
{
public:
    void evaluate(const ASTNode &node);
    string evaluateFunctionCall(const ASTNode &node);

private:
    map<string, int> intVariables;
    map<string, long> longVariables;
    map<string, float> floatVariables;
    map<string, double> doubleVariables;
    map<string, bool> boolVariables;
    map<string, string> stringVariables;
    map<string, char> charVariables;

    map<string, ASTNode> functions; 
    map<string, string> variables;  

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
    string getInput();

    
    bool isInteger(const string &value);
    bool isFloat(const string &value);
    bool isBool(const string &value);  
    bool isChar(const string &value);   
    bool isString(const string &value); 
    bool isLong(const string &value);  
    bool isDouble(const string &value); 
};

#endif