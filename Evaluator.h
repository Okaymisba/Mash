#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <map>
#include "structs/ASTNode.h"

using namespace std;

class Evaluator
{
public:
    void evaluate(const ASTNode &node);

private:
    map<string, int> intVariables;
    map<string, double> floatVariables;
    map<string, string> stringVariables;
    map<string, bool> boolVariables;

    int evaluateIntegerExpression(const ASTNode &node);
    double evaluateFloatExpression(const ASTNode &node);
    string evaluateStringExpression(const ASTNode &node);
    bool evaluateBooleanExpression(const ASTNode &node);

    void handleAssignment(const ASTNode &node);
    void handlePrint(const ASTNode &node);
};

#endif
