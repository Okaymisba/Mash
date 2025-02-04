#include "../../Parser.h"
#include <stdexcept>

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