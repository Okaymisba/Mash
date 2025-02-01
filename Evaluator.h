#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <unordered_map>
#include <string>
#include "structs/ASTNode.h"

using namespace std;

class Evaluator
{
public:
    void evaluate(const ASTNode &node);

private:
    unordered_map<string, int> intTable;
    unordered_map<string, double> doubleTable;
    unordered_map<string, string> stringTable;
    unordered_map<string, char> charTable;
    unordered_map<string, bool> boolTable;

    void evaluateAssignment(const ASTNode &node);
    void evaluatePrint(const ASTNode &node);
    string evaluateExpression(const ASTNode &node);
};

#endif
