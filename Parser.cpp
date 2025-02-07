#include <iostream>
#include "Parser.h"
#include "Tokenizer.h"

using namespace std;

ASTNode Parser::parse()
{
    ASTNode root("PROGRAM");
    while (peek().type != "EOF")
    {
        if (peek().type == "LINE_BREAK")
        {
            consume("LINE_BREAK");
        }
        else
        {
            ASTNode statement = parseStatement();
            root.children.push_back(statement);
            if (peek().type == "SEMICOLON")
            {
                consume("SEMICOLON");
            }
        }
    }
    return root;
}

ASTNode Parser::parseAssignment()
{
    Token identifier = consume("IDENTIFIER");
    consume("ASSIGN");
    
    ASTNode assignment("ASSIGNMENT");
    assignment.children.push_back(ASTNode("IDENTIFIER", identifier.value));

    // Wrap arithmetic expressions inside an EXPRESSION node
    ASTNode expressionNode = parseExpression();
    assignment.children.push_back(expressionNode);

    consume("SEMICOLON");
    consume("LINE_BREAK");
    
    return assignment;
}

ASTNode Parser::parseExpression()
{
    ASTNode left = parseTerm();

    while (peek().type == "ARITHMETIC_OPERATOR")
    {
        Token op = consume("ARITHMETIC_OPERATOR");
        ASTNode right = parseTerm();

        ASTNode expr("EXPRESSION");
        expr.children.push_back(left);
        expr.children.push_back(ASTNode("ARITHMETIC_OPERATOR", op.value));
        expr.children.push_back(right);

        left = expr;
    }

    return left;
}

ASTNode Parser::parseTerm()
{
    Token token = peek();
    if (token.type == "INTEGER" || token.type == "FLOAT" || token.type == "DOUBLE")
    {
        return ASTNode(token.type, consume(token.type).value);
    }
    else if (token.type == "IDENTIFIER")
    {
        return ASTNode("IDENTIFIER", consume("IDENTIFIER").value);
    }
    else
    {
        throw runtime_error("Unexpected token in expression: " + token.value);
    }
}

ASTNode Parser::parsePrintStatement()
{
    consume("PRINT");
    consume("OPEN_ROUND_BRACKET");
    ASTNode printNode("PRINT");

    while (peek().type != "CLOSE_ROUND_BRACKET")
    {
        ASTNode expression = parseExpression();
        printNode.children.push_back(expression);
    }

    consume("CLOSE_ROUND_BRACKET");
    if (peek().type == "SEMICOLON")
    {
        consume("SEMICOLON");
    }
    return printNode;
}

ASTNode Parser::parseIfStatement()
{
    consume("CHECK_IF");
    ASTNode ifStatement("IF STATEMENT");

    ASTNode ifNode("IF");
    ASTNode condition = parseCondition();
    ifNode.children.push_back(condition);
    ASTNode body = parseBody();
    ifNode.children.push_back(body);
    ifStatement.children.push_back(ifNode);

    while (peek().type == "ELSE IF")
    {
        consume("ELSE IF");
        ASTNode elseIfNode("ELSE IF");
        ASTNode condition = parseCondition();
        elseIfNode.children.push_back(condition);
        ASTNode body = parseBody();
        elseIfNode.children.push_back(body);
        ifStatement.children.push_back(elseIfNode);
    }

    if (peek().type == "ELSE")
    {
        consume("ELSE");
        ASTNode elseNode("ELSE");
        ASTNode body = parseBody();
        elseNode.children.push_back(body);
        ifStatement.children.push_back(elseNode);
    }

    return ifStatement;
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
    else if (token.type == "CHECK_IF")
    {
        return parseIfStatement();
    }
    else
    {
        throw runtime_error("Invalid statement: unexpected token " + token.type);
    }
}
