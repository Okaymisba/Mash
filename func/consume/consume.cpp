#include "../../Parser.h"
#include <stdexcept>

/**
 * Consumes the next token in the sequence if it matches the expected type.
 * If the next token type matches the expected type, increments the currentIndex
 * and returns the token. If not, throws a runtime error indicating the mismatch.
 *
 * @param expectedType The type of token expected to be consumed.
 * @return The token that was consumed.
 * @throws runtime_error If the next token does not match the expected type.
 */

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