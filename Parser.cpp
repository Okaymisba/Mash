#include <iostream>
#include "Parser.h"
#include "Tokenizer.h"

ASTNode Parser::parse()
{
    ASTNode root("PROGRAM");
    while (peek().type != "EOF")
    {
        ASTNode statement = parseStatement();
        root.children.push_back(statement);
        if (peek().type == "SEMICOLON")
        {
            consume("SEMICOLON");
        }
    }
    return root;
};

Token Parser::peek()
{
    if (currentIndex < tokens.size())
    {
        return tokens[currentIndex];
    }
    return Token("EOF", "");
};

Token Parser::consume(const string &expectedType)
{
    Token token = peek();
    if (token.type == expectedType)
    {
        currentIndex++;
        return token;
    }
    else
    {
        throw runtime_error("Unexpected token: expected " + expectedType + ", got " + token.type);
    }
}

// TODO: This needs to be further modified to handle the parsing to the semicolon
ASTNode Parser::parseExpresseion()
{
    Token token = peek();
    if (token.type == "IDENTIFIER" || token.type == "NUMBER")
    {
        consume(token.type);
        ASTNode node("LITERAL", token.value);
        return node;
    }
    else
    {
        throw runtime_error("Invalid expression: expected NUMBER or IDENTIFIER, got " + token.type);
    }
}

ASTNode Parser::parseAssignment()
{
    Token identifier = consume("IDENTIFIER");
    consume("ASSIGN");
    ASTNode value = parseExpresseion();
    ASTNode assignment("ASSIGNMENT");
    assignment.children.push_back(ASTNode("IDENTIFIER", identifier.value));
    assignment.children.push_back(value);
    return assignment;
}

ASTNode Parser::parsePrintStatement()
{
    consume("PRINT");
    ASTNode expression = parseExpresseion();
    ASTNode printNode("PRINT");
    printNode.children.push_back(expression);
    return printNode;
}

ASTNode Parser::parseStatement()
{
    Token token = peek();
    if (token.type == "PRINT")
    {
        return parsePrintStatement();
    }
    else if (token.type == "IDENTIFIER")
    {
        return parseAssignment();
    }
    else
    {
        throw runtime_error("Invalid statement: unexpected token " + token.type);
    }
}