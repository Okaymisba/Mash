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
            ASTNode statement = parseStatement(); // parseStatement() in Parcer.cpp
            root.children.push_back(statement);
            if (peek().type == "SEMICOLON")
            {
                consume("SEMICOLON");
            }
        }
    }
    return root;
}

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
    ASTNode assignment("ASSIGNMENT");

    ASTNode identifierNode("IDENTIFIER", identifier.value);

    if (peek().type == "COLON")
    {
        consume("COLON");
        Token type = consume("TYPE");
        ASTNode datatype(type.type, type.value);
        identifierNode.children.push_back(datatype);

        assignment.children.push_back(identifierNode);

        consume("ASSIGN");

        // Wraping arithmetic expressions inside an EXPRESSION node
        ASTNode expressionNode = parseExpression(); // parseExpression() in func/parseExpression/parseExpression.cpp
        if (ValidateDataType(identifierNode, expressionNode))
        {
            assignment.children.push_back(expressionNode);
            consume("SEMICOLON");
            consume("LINE_BREAK");

            return assignment;
        }
        else
            throw runtime_error("Unexpected type: Declared " + identifierNode.children[0].value + " but got " + expressionNode.type);
    }

    else
    {

        assignment.children.push_back(identifierNode);

        consume("ASSIGN");

        // Wraping arithmetic expressions inside an EXPRESSION node
        ASTNode expressionNode = parseExpression(); // parseExpression() in func/parseExpression/parseExpression.cpp
        assignment.children.push_back(expressionNode);

        consume("SEMICOLON");
        consume("LINE_BREAK");
    }
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
        ASTNode expression = parseExpression(); // parseExpression() in func/parseExpression/parseExpression.cpp
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
    ASTNode condition = parseCondition(); // parseCondition() in func/parseCondition/parseCondition.cpp
    ifNode.children.push_back(condition);
    ASTNode body = parseBody(); // parseBody() in func/parseBody/parseBody.cpp
    ifNode.children.push_back(body);
    ifStatement.children.push_back(ifNode);

    while (peek().type == "ELSE IF")
    {
        consume("ELSE IF");
        ASTNode elseIfNode("ELSE IF");
        ASTNode condition = parseCondition(); // parseCondition() in func/parseCondition/parseCondition.cpp
        elseIfNode.children.push_back(condition);
        ASTNode body = parseBody(); // parseBody() in func/parseBody/parseBody.cpp
        elseIfNode.children.push_back(body);
        ifStatement.children.push_back(elseIfNode);
    }

    if (peek().type == "ELSE")
    {
        consume("ELSE");
        ASTNode elseNode("ELSE");
        ASTNode body = parseBody(); // parseBody() in func/parseBody/parseBody.cpp
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
    ASTNode condition = parseCondition(); // parseCondition() in func/parseCondition/parseCondition.cpp
    whileNode.children.push_back(condition);
    ASTNode body = parseBody(); // parseBody() in func/parseBody/parseBody.cpp
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
        return parsePrintStatement(); // parsePrintStatement() in Parser.cpp
    }
    else if (token.type == "IDENTIFIER")
    {
        return parseAssignment(); // parseAssignment() in Parser.cpp
    }
    else if (token.type == "CHECK_IF")
    {
        return parseIfStatement(); // parseIfStatement() in Parser.cpp
    }
    else if (token.type == "WHILE")
    {
        return parseWhileLoop(); // parseWhileLoop() in Parser.cpp
    }
    else if (token.type == "FOR")
    {
        return parseForLoop();
    }
    else if (token.type == "FUNCTION")
    {
        return parseFunction();
    }
    else
    {
        throw runtime_error("Invalid statement: unexpected token " + token.type);
    }
}

/**
 *Parses a for loop statement and generates an Abstract Syntax Tree node.
 *This function parses a for loop which follows the syntax for(<identifier> in <starting-value> to <ending value>){body}
 *The function constructs an AST node with the type "FOR" and add three children:
 * 1. Loop variable (IDENTIFIER)
 * 2. A sub node of type "RANGE" containing child nodes of starting and ending values
 * 3. The loop body, parsed by calling parseBody()
 * @return An Abstract Syntax Tree representing for loop statement
 */

ASTNode Parser::parseForLoop()
{
    consume("FOR");

    ASTNode ForNode("FOR");
    consume("OPEN_ROUND_BRACKET");

    Token iden = consume("IDENTIFIER");
    ASTNode identifierNode("IDENTIFIER", iden.value);
    ForNode.children.push_back(identifierNode);

    consume("IN");

    ASTNode rangeNode("RANGE");

    ASTNode start("START");

    ASTNode start_value = parseExpression();
    start.children.push_back(start_value);
    rangeNode.children.push_back(start);
    Token range_type = peek();
    if (range_type.type == "TO" || range_type.type == "DOWNTO" || range_type.type == "DOWNUNTIL" || range_type.type == "UNTIL")
    {
        consume(range_type.type);
        ASTNode RangeType(range_type.type);
        rangeNode.children.push_back(RangeType);
    }
    else
    {
        throw runtime_error("Invalid range type: Expected to, until, downuntil, downto");
    }
    ASTNode end("END");
    ASTNode end_value = parseExpression();
    end.children.push_back(end_value);
    rangeNode.children.push_back(end);

    ForNode.children.push_back(rangeNode);

    if (peek().type == "STEP")
    {
        consume("STEP");
        ASTNode step("STEP");
        ASTNode step_value = parseExpression(); // Parse step expression
        step.children.push_back(step_value);
        ForNode.children.push_back(step);
    }
    consume("CLOSE_ROUND_BRACKET");

    ASTNode body = parseBody(); // parseBody() in func/parseBody/ParseBody.cpp
    ForNode.children.push_back(body);

    return ForNode;
}
ASTNode Parser::parseFunction()
{
    consume("FUNCTION");

    ASTNode Function("FUNCTION");

    // Function name
    Token FunctName = consume("IDENTIFIER");
    Function.children.push_back(ASTNode(FunctName.type, FunctName.value));

    consume("OPEN_ROUND_BRACKET");

    // Parameters node
    ASTNode Parameters("PARAMETERS");

    if (peek().type != "CLOSE_ROUND_BRACKET")
    {
        // Parse first parameter
        Token par_type = consume("TYPE");
        Token par = consume("IDENTIFIER");
        Parameters.children.push_back(ASTNode(par_type.type, par_type.value));
        Parameters.children.push_back(ASTNode(par.type, par.value));

        // Parse additional parameters
        while (peek().type == "COMMA")
        {
            consume("COMMA");
            Token par_type2 = consume("TYPE");
            Token par2 = consume("IDENTIFIER");
            Parameters.children.push_back(ASTNode(par_type2.type, par_type2.value));
            Parameters.children.push_back(ASTNode(par2.type, par2.value));
        }
    }

    consume("CLOSE_ROUND_BRACKET");
    Function.children.push_back(Parameters);

    // Function body
    ASTNode parseFunctionBody = parseBody();
    Function.children.push_back(parseFunctionBody);

    return Function;
}
