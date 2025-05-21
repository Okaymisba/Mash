#include "../../Parser.h"

ASTNode Parser::parseInput()
{
    string input;
    consume("INPUT");
    ASTNode inputNode("INPUT");

    return inputNode;
}