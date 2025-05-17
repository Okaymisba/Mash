#include "../../Parser.h"
#include <iostream>

/**
 * Parses a function body and returns an Abstract Syntax Tree node.
 *
 * This function processes a block of statements enclosed within curly brackets
 * and constructs an AST node with the type "FUNC_BODY". It skips initial and
 * trailing line breaks and consumes the opening curly bracket. The function
 * iterates through tokens, adding parsed return statements and other
 * statements to the function body's children until a closing curly bracket
 * is encountered. If an unexpected end of file is reached before finding the
 * closing bracket, a runtime error is thrown. Parsing errors within statements
 * are caught and logged as standard error output.
 *
 * @return An Abstract Syntax Tree node representing the function body.
 * @throws std::runtime_error If the closing curly bracket is missing or
 *                            parsing a statement fails.
 */

ASTNode Parser::parseFuncBody()
{
    while (peek().type == "LINE_BREAK")
    {
        consume("LINE_BREAK");
    }

    consume("OPEN_CURLY_BRACKET");

    ASTNode funcBody("FUNC_BODY");

    while (peek().type != "CLOSE_CURLY_BRACKET")
    {
        if (peek().type == "EOF")
        {
            throw std::runtime_error("Unexpected end of file. Missing '}' to close function body.");
        }

        try
        {
            if (peek().type == "RETURN")
            {
                ASTNode returnNode = parseReturnStatement();
                funcBody.children.push_back(returnNode);
            }
            else if (peek().type == "LINE_BREAK")
            {
                consume("LINE_BREAK");
            }
            else
            {
                ASTNode statement = parseStatement();
                funcBody.children.push_back(statement);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing statement: " << e.what() << std::endl;
            throw;
        }
    }

    consume("CLOSE_CURLY_BRACKET");

    while (peek().type == "LINE_BREAK")
    {
        consume("LINE_BREAK");
    }

    return funcBody;
}

ASTNode Parser::parseReturnStatement()
{
    consume("RETURN");

    ASTNode returnNode("RETURN");

    if (peek().type != "SEMICOLON")
    {
        ASTNode expression = parseExpression();
        returnNode.children.push_back(expression);
    }

    consume("SEMICOLON");
    return returnNode;
}