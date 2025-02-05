#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <map>
#include "structs/ASTNode.h"

using namespace std;

class Evaluator {
public:
    void evaluate(const ASTNode &node);

private:
    unordered_map<string, int> intTable;
    unordered_map<string, double> doubleTable;
    unordered_map<string, string> stringTable;
    unordered_map<string, char> charTable;
    unordered_map<string, bool> boolTable;

    map<string, int> intVariables;
    map<string, double> floatVariables;
    map<string, string> stringVariables;
    map<string, bool> boolVariables;

    void evaluateAssignment(const ASTNode &node);
    void evaluatePrint(const ASTNode &node);
    string evaluateExpression(const ASTNode &node);
    int evaluateIntegerExpression(const ASTNode &node);
    double evaluateFloatExpression(const ASTNode &node);
    string evaluateStringExpression(const ASTNode &node);
    bool evaluateBooleanExpression(const ASTNode &node);

    void handleAssignment(const ASTNode &node);
    void handlePrint(const ASTNode &node);
};

#endif // EVALUATOR_H
