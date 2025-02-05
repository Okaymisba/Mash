#include "Evaluator.h"

void Evaluator::evaluate(const ASTNode &node) {
    if (node.type == "PROGRAM") {
        for (const auto &child : node.children) {
            evaluate(child);
        }
    } else if (node.type == "ASSIGNMENT") {
        handleAssignment(node);
    } else if (node.type == "PRINT") {
        handlePrint(node);
    } else {
        for (const auto &child : node.children) {
            evaluate(child);
        }
    }
}

void Evaluator::handleAssignment(const ASTNode &node) {
    if (node.children.size() < 2) {
        throw runtime_error("Invalid assignment statement.");
    }

    string varName = node.children[0].value;
    ASTNode expressionNode = node.children[1];

    if (expressionNode.type == "INTEGER") {
        intVariables[varName] = stoi(expressionNode.value);
    } else if (expressionNode.type == "FLOAT") {
        floatVariables[varName] = stod(expressionNode.value);
    } else if (expressionNode.type == "STRING") {
        stringVariables[varName] = expressionNode.value;
    } else if (expressionNode.type == "BOOL") {
        boolVariables[varName] = (expressionNode.value == "True");
    } else if (expressionNode.type == "ARITHMETIC_OPERATOR") {
        int result = evaluateIntegerExpression(expressionNode);
        intVariables[varName] = result;
    } else {
        cerr << "Unknown node type: " << node.type << endl;
        throw runtime_error("Unsupported assignment type.");
    }
}

void Evaluator::handlePrint(const ASTNode &node) {
    if (node.children.size() < 1) {
        throw runtime_error("Print statement has no argument.");
    }

    string varName = node.children[0].value;
    string varValue = evaluateExpression(node.children[0]);

    // Print based on variable type
    if (intVariables.count(varName)) {
        cout << intVariables[varName] << endl;
    } else if (floatVariables.count(varName)) {
        cout << floatVariables[varName] << endl;
    } else if (stringVariables.count(varName)) {
        cout << stringVariables[varName] << endl;
    } else if (boolVariables.count(varName)) {
        cout << (boolVariables[varName] ? "True" : "False") << endl;
    } else {
        cerr << "Error: Undefined variable - " << varName << endl;
    }
}

string Evaluator::evaluateExpression(const ASTNode &node) {
    if (node.type == "NUMBER" || node.type == "STRING" || node.type == "IDENTIFIER") {
        return node.value;
    }
    throw runtime_error("Invalid expression.");
}

int Evaluator::evaluateIntegerExpression(const ASTNode &node) {
    if (node.type == "INTEGER") {
        return stoi(node.value);
    }

    if (node.children.size() == 2) {
        int left = evaluateIntegerExpression(node.children[0]);
        int right = evaluateIntegerExpression(node.children[1]);

        if (node.value == "+") {
            return left + right;
        } else if (node.value == "-") {
            return left - right;
        } else if (node.value == "*") {
            return left * right;
        } else if (node.value == "/") {
            if (right == 0) throw runtime_error("Division by zero.");
            return left / right;
        } else if (node.value == "%") {
            return left % right;
        }
    }
    throw runtime_error("Invalid arithmetic expression.");
}

double Evaluator::evaluateFloatExpression(const ASTNode &node) {
    if (node.type == "FLOAT") {
        return stod(node.value);
    }
    throw runtime_error("Invalid float expression.");
}

string Evaluator::evaluateStringExpression(const ASTNode &node) {
    if (node.type == "STRING" || node.type == "IDENTIFIER") {
        return node.value;
    }
    throw runtime_error("Invalid string expression.");
}

bool Evaluator::evaluateBooleanExpression(const ASTNode &node) {
    if (node.type == "BOOL") {
        return node.value == "True";
    }
    throw runtime_error("Invalid boolean expression.");
}
