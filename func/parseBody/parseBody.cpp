#include "../../Parser.h"

/**
 * @return An AST node representing the body of a block
 *
 * @details
 * This function parses a block of statements enclosed within curly brackets.
 * It first consumes any leading line breaks and the opening curly bracket.
 * Then, it continues to parse and add statements as children to an AST node
 * of type BODY, skipping over any line breaks, until it encounters a closing
 * curly bracket. Finally, it consumes the closing curly bracket and returns
 * the constructed BODY node.
 */

 ASTNode Parser::parseBody()
 {
     while (peek().type == "LINE_BREAK")
     {
         consume("LINE_BREAK");
     }
 
     consume("OPEN_CURLY_BRACKET");
     ASTNode body("BODY");
 
     while (peek().type != "CLOSE_CURLY_BRACKET")
     {
         if (peek().type == "LINE_BREAK")
         {
             consume("LINE_BREAK");
         }
         else if (peek().type == "RETURN")
         {
             consume("RETURN");
             ASTNode Return("RETURN");
             ASTNode returnExpression = parseExpression();
             Return.children.push_back(returnExpression);
             body.children.push_back(Return);
         }
         else
         {
             ASTNode statement = parseStatement();
             body.children.push_back(statement);
         }
     }
 
     consume("CLOSE_CURLY_BRACKET");
 
     while (peek().type == "LINE_BREAK")
     {
         consume("LINE_BREAK");
     }
 
     return body;
 }
 
