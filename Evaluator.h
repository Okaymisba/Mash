#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <unordered_map>
#include "structs/ASTNode.h"

using namespace std;

class Evaluator
{
public:
    void evaluate(const ASTNode &node);

private:
    unordered_map<string, string> symbolTable;

    void evaluateAssignment(const ASTNode &node);
    void evaluatePrint(const ASTNode &node);
};

#endif
