#include "../../Parser.h"

Token Parser::peek()
{
    if (currentIndex < tokens.size())
    {
        return tokens[currentIndex];
    }
    return Token("EOF", "");
};