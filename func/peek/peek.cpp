#include "../../Parser.h"

/**
 * Returns the current token in the sequence without consuming it.
 * 
 * @return The current token if there are more tokens in the sequence;
 *         otherwise, returns a token with type "EOF" and an empty value.
 */

Token Parser::peek()
{
    if (currentIndex < tokens.size())
    {
        return tokens[currentIndex];
    }
    return Token("EOF", "");
};