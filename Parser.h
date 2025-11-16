#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "structs/Token.h"
#include "structs/ASTNode.h"

using namespace std;

class Parser {
public:
    explicit Parser(const vector<Token> &tokens) : tokens(tokens), currentIndex(0) {
    }

    ASTNode parse();

private:
    vector<Token> tokens;
    size_t currentIndex;
    bool insideFunction;

    Token peek();

    Token consume(const string &expectedType);

    int getPrecedence(const string &op);

    bool ValidateDataType(const ASTNode &node1, const ASTNode &node2);

    ASTNode parseExpression(int minimumPrecedence = 0);

    ASTNode parseTerm();

    ASTNode parseAssignment();

    ASTNode parsePrintStatement();

    ASTNode parseIfStatement();

    ASTNode parseWhileLoop();

    ASTNode parseCondition();

    ASTNode parseBody();

    ASTNode parseFuncBody();

    ASTNode parseReturnStatement();

    ASTNode parseStatement();

    ASTNode parseForLoop();

    ASTNode parseFunctionCall();

    ASTNode parseFunction();

    ASTNode parseDatabaseCall();

    ASTNode parseInput();
};

#endif
