#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include "structs/Token.h" // Ensure only this file defines Token

using namespace std;

class Tokenizer {
public:
    vector<Token> tokenize(const string &code); // Ensure signature matches in .cpp
};

#endif