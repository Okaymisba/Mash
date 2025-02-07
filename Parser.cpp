#include <iostream>
#include "Parser.h"
#include "Tokenizer.h"

using namespace std;

/**
 * Parses the tokens and returns an Abstract Syntax Tree root node.
 *
 * This function parses the tokens and returns an Abstract Syntax Tree root node.
 * The root node has type "PROGRAM" and contains all the statements in the program.
 * The statements are parsed by calling the parseStatement() function.
 * If a statement is followed by a semicolon, the semicolon is consumed.
 * The function continues to parse tokens until it encounters an EOF token.
 *
 * @return An Abstract Syntax Tree root node representing the program.
 */
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
};

/**
 * Parses an assignment statement and returns an Abstract Syntax Tree node.
 *
 * This function parses an assignment statement and returns an Abstract Syntax Tree node.
 * The node has type "ASSIGNMENT" and has two children: an identifier and a value.
 * The value is parsed by calling the parseExpression() function.
 * The function continues to parse tokens until it encounters a semicolon.
 * The semicolon and line break are consumed.
 *
 * @return An Abstract Syntax Tree node representing the assignment statement.
 */
ASTNode Parser::parseAssignment()
{
    Token identifier = consume("IDENTIFIER");
    consume("ASSIGN");
    ASTNode assignment("ASSIGNMENT");
    assignment.children.push_back(ASTNode("IDENTIFIER", identifier.value));

    while (peek().type != "SEMICOLON")
    {
        ASTNode value = parseExpression();
        assignment.children.push_back(value);
    }
    consume("SEMICOLON");
    consume("LINE_BREAK");
    return assignment;
}

/**
 * Parses a print statement and returns an Abstract Syntax Tree node.
 *
 * This function parses a print statement, which starts with the keyword PRINT
 * followed by an expression enclosed in parentheses. It constructs an AST
 * node with the type "PRINT" and adds the parsed expressions as its children.
 * The function consumes the PRINT keyword, the opening and closing round
 * brackets, and optionally a semicolon after the closing bracket.
 *
 * @return An Abstract Syntax Tree node representing the print statement.
 */

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

/**
 * Parses an if statement and returns an Abstract Syntax Tree node.
 *
 * This function parses an if statement, which consists of one or more if and
 * else if clauses followed by an optional else clause. It constructs an AST
 * node with the type "IF STATEMENT" and adds the parsed if and else if clauses
 * as its children. Each if and else if clause is parsed as a separate node
 * with the type "IF" or "ELSE IF", respectively, and the condition and body
 * of each clause are added as children of the clause node. The else clause,
 * if present, is also parsed as a separate node with the type "ELSE" and its
 * body added as a child of the else node.
 *
 * @return An Abstract Syntax Tree node representing the if statement.
 */
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

/**
 * Parses a while loop statement and returns an Abstract Syntax Tree node.
 *
 * This function parses a while loop, which consists of a condition and a body.
 * It constructs an AST node with the type "WHILE" and adds the parsed condition
 * and body as its children. The condition is parsed by calling the parseCondition()
 * function, and the body is parsed by calling the parseBody() function.
 *
 * @return An Abstract Syntax Tree node representing the while loop statement.
 */
ASTNode Parser::parseWhileLoop()
{
    consume("WHILE");
    ASTNode whileNode("WHILE");
    ASTNode condition = parseCondition();
    whileNode.children.push_back(condition);
    ASTNode body = parseBody();
    whileNode.children.push_back(body);
    return whileNode;
}

/**
 * Parses the tokens from the token stream and returns an Abstract Syntax Tree node.
 *
 * This function determines the type of statement based on the current token and
 * delegates the parsing to the appropriate specific parse function, such as
 * parsePrintStatement(), parseAssignment(), or parseIfStatement(). If the token
 * type does not match any recognized statement type, a runtime error is thrown.
 *
 * @return An Abstract Syntax Tree node representing the parsed statement.
 * @throws runtime_error If the token type is not a valid statement type.
 */

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
    else if (token.type == "WHILE")
    {
        return parseWhileLoop();
    }
    else
    {
        throw runtime_error("Invalid statement: unexpected token " + token.type);
    }
}