#include "Evaluator.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>

using namespace std;

/**
 * Evaluates an Abstract Syntax Tree node.
 *
 * This function evaluates an Abstract Syntax Tree node by checking its type and
 * delegating the evaluation to the appropriate specific evaluation function.
 * If the node type is not recognized, a runtime error is thrown.
 */

void Evaluator::evaluate(const ASTNode &node) {
    if (node.type == "PROGRAM") {
        for (const auto &child: node.children) {
            evaluate(child);
        }
    } else if (node.type == "ASSIGNMENT") {
        evaluateAssignment(node);
    } else if (node.type == "PRINT") {
        evaluatePrint(node);
    } else if (node.type == "IF STATEMENT") {
        evaluateIfStatement(node);
    } else if (node.type == "WHILE") {
        evaluateWhileLoop(node);
    } else if (node.type == "FOR") {
        evaluateForLoop(node);
    } else if (node.type == "FUNCTION") {
        string functionName = node.children[0].value;
        functions[functionName] = node;
    } else if (node.type == "FUNCTION_CALL") {
        evaluateFunctionCall(node);
    } else if (node.type == "DATABASE_CALL") {
        if (!node.children.empty()) {
            string query = node.children[0].value;
            if (query.size() >= 2 &&
                ((query.front() == '"' && query.back() == '"') ||
                 (query.front() == '\'' && query.back() == '\''))) {
                query = query.substr(1, query.size() - 2);
            }
            string result = executeDatabaseQuery(query);
        } else {
            throw runtime_error("Database call is missing query");
        }
    } else {
        throw runtime_error("Unknown node type: " + node.type);
    }
}

/**
 * Evaluates an assignment statement by setting the value of a variable.
 *
 * This function evaluates an assignment statement by extracting the identifier
 * and value from the Abstract Syntax Tree node and setting the value of the
 * variable using the appropriate type-specific map. The variable type is
 * determined by examining the value string.
 *
 * @param node The Abstract Syntax Tree node representing the assignment statement.
 * @return An empty string.
 * @throws runtime_error If the assignment node does not have exactly two children.
 */

string Evaluator::evaluateAssignment(const ASTNode &node) {
    if (node.children.size() < 2) {
        throw runtime_error("Invalid assignment: expected identifier and value");
    }

    string identifier = node.children[0].value;

    if (node.children[1].type == "STRING") {
        setVariableValue(identifier, node.children[1].value, "STRING");
    } else if (node.children[1].type == "INPUT") {
        string input = getInput();
        if (isInteger(input)) {
            setVariableValue(identifier, input, "INTEGER");
        } else if (isFloat(input)) {
            setVariableValue(identifier, input, "FLOAT");
        } else if (isDouble(input)) {
            setVariableValue(identifier, input, "DOUBLE");
        } else if (isLong(input)) {
            setVariableValue(identifier, input, "LONG");
        } else if (isChar(input)) {
            setVariableValue(identifier, input, "CHAR");
        } else {
            setVariableValue(identifier, input, "STRING");
        }
    } else {
        string value = evaluateExpression(node.children[1]);

        if (value.find('.') != string::npos) {
            if (value.size() > 8) {
                setVariableValue(identifier, value, "DOUBLE");
            } else {
                setVariableValue(identifier, value, "FLOAT");
            }
        } else {
            setVariableValue(identifier, value, "INTEGER");
        }
    }

    return "";
}

/**
 * Evaluates a print statement by printing the values of its children to the console.
 *
 * This function evaluates a print statement by iterating over its children and
 * printing their values to the console. The value of each child is determined
 * by its type:
 * - `NUMBER`, `INTEGER`, `FLOAT`, `DOUBLE`: The numerical value is printed as is.
 * - `IDENTIFIER`: The value of the variable with the given name is printed.
 * - `EXPRESSION`: The expression is evaluated and its result is printed.
 * - `STRING`: The string value is printed as is.
 * - `FUNCTION_CALL`: The function is called and its return value is printed.
 * - Other types: A runtime error is thrown because the expression type is not supported.
 *
 * @param node The Abstract Syntax Tree node representing the print statement.
 * @return An empty string.
 * @throws runtime_error If an unsupported expression type is encountered.
 */
string Evaluator::evaluatePrint(const ASTNode &node) {
    if (node.children.empty()) {
        cout << endl;
        return "";
    }

    for (const auto &child: node.children) {
        if (child.type == "NUMBER" || child.type == "INTEGER" || child.type == "FLOAT" || child.type == "DOUBLE") {
            cout << child.value;
        } else if (child.type == "IDENTIFIER") {
            auto value = getVariableValue(child.value);
            cout << value;
        } else if (child.type == "EXPRESSION") {
            cout << evaluateExpression(child);
        } else if (child.type == "STRING") {
            cout << child.value;
        } else if (child.type == "FUNCTION_CALL") {
            cout << evaluateFunctionCall(child);
        } else {
            throw runtime_error("Unsupported expression type: " + node.type);
        }
    }

    return "";
}

/**
 * Evaluates an if statement by checking conditions and executing bodies.
 *
 * This function iterates over the children of the given AST node and evaluates
 * the condition and body of each if and else if clause. If the condition is
 * satisfied, the body is executed and the function returns. If none of the
 * conditions are satisfied, the else clause is executed if present.
 *
 * @param node The Abstract Syntax Tree node representing the if statement.
 */

void Evaluator::evaluateIfStatement(const ASTNode &node) {
    bool conditionMet = false;

    for (const auto &child: node.children) {
        if (child.type == "IF" || (child.type == "ELSE IF" && !conditionMet)) {
            if (evaluateCondition(child.children[0]) == "true") {
                evaluateBody(child.children[1]);
                conditionMet = true;
            }
        } else if (child.type == "ELSE" && !conditionMet) {
            evaluateBody(child.children[0]);
            conditionMet = true;
        }
    }
}

/**
 * Evaluates a while loop statement by checking the condition and executing the body.
 *
 * This function evaluates the condition of the given while loop node and executes
 * the body if the condition is satisfied. The condition is evaluated using the
 * evaluateCondition() function, and the body is evaluated using the evaluateBody()
 * function. The process is repeated until the condition is no longer satisfied.
 *
 * @param node The Abstract Syntax Tree node representing the while loop statement.
 */

void Evaluator::evaluateWhileLoop(const ASTNode &node) {
    while (evaluateCondition(node.children[0]) == "true") {
        evaluateBody(node.children[1]);
    }
}

/**
 * Evaluates a for loop statement by initializing the loop variable and iterating through the range.
 *
 * This function evaluates a for loop by:
 * 1. Getting the loop variable identifier
 * 2. Extracting the range information (start, type, end)
 * 3. Optionally getting the step value
 * 4. Executing the loop body for each value in the range
 *
 * @param node The Abstract Syntax Tree node representing the for loop statement.
 */

void Evaluator::evaluateForLoop(const ASTNode &node) {
    const string &identifier = node.children[0].value;
    const ASTNode &rangeNode = node.children[1];
    const ASTNode &body = node.children.back();

    int start = stoi(evaluateExpression(rangeNode.children[0].children[0]));
    int end = stoi(evaluateExpression(rangeNode.children[2].children[0]));

    int step = 1;
    if (node.children.size() > 3) {
        step = stoi(evaluateExpression(node.children[2].children[0]));
    }

    const string &rangeType = rangeNode.children[1].type;

    char numBuffer[32];

    auto setVarAndEval = [&](int val) {
        sprintf(numBuffer, "%d", val);
        setVariableValue(identifier, numBuffer, "INTEGER");
        evaluateBody(body);
    };

    if (rangeType == "TO") {
        for (int i = start; i <= end; i += step) {
            setVarAndEval(i);
        }
    } else if (rangeType == "DOWNTO") {
        for (int i = start; i >= end; i -= step) {
            setVarAndEval(i);
        }
    } else if (rangeType == "UNTIL") {
        for (int i = start; i < end; i += step) {
            setVarAndEval(i);
        }
    } else if (rangeType == "DOWNUNTIL") {
        for (int i = start; i > end; i -= step) {
            setVarAndEval(i);
        }
    } else {
        throw runtime_error("Invalid range type in for loop: " + rangeType);
    }
}

bool Evaluator::isInteger(const string &value) {
    return regex_match(value, regex("^-?\\d+$"));
}

bool Evaluator::isFloat(const string &value) {
    return regex_match(value, regex("^-?\\d*\\.\\d+$"));
}

bool Evaluator::isBool(const string &value) {
    return value == "true" || value == "false";
}

bool Evaluator::isChar(const string &value) {
    return value.size() == 1;
}

bool Evaluator::isString(const string &value) {
    return !value.empty();
}

bool Evaluator::isLong(const string &value) {
    return isInteger(value);
}

bool Evaluator::isDouble(const string &value) {
    return isFloat(value);
}

string Evaluator::executeDatabaseQuery(const string &query) {
    string command = "./exe/MashDB --json \"" + query + "\"";
    array<char, 128> buffer;
    string result;

    unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw runtime_error("Failed to execute database query");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    cout << result << endl;

    return result;
}

string Evaluator::evaluateFunctionCall(const ASTNode &node) {
    string functionName = node.value;

    if (functions.find(functionName) == functions.end()) {
        throw runtime_error("Undefined function: " + functionName);
    }

    ASTNode functionDefinition = functions[functionName];

    ASTNode parameters = functionDefinition.children[1];
    ASTNode body = functionDefinition.children[2];

    if (parameters.children.size() != node.children.size()) {
        throw runtime_error("Argument count mismatch for function: " + functionName);
    }

    map<string, string> localVariables;

    for (size_t i = 0; i < node.children.size(); ++i) {
        string paramName = parameters.children[i].children[1].value;
        string argValue = evaluateExpression(node.children[i]);
        string paramType;
        if (isInteger(argValue)) {
            paramType = "INTEGER";
        } else if (isFloat(argValue)) {
            paramType = "FLOAT";
        } else {
            paramType = "STRING";
        }

        setVariableValue(paramName, argValue, paramType);
    }

    auto savedVariables = variables;

    variables = localVariables;

    string result;
    try {
        result = evaluateBody(body);
    } catch (const ReturnException &e) {
        result = e.value();
    }

    variables = savedVariables;

    return result;
}
