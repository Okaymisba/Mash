#ifndef TOKENIIZER_H
#define TOKENIZER_H

#include <string>
#include <iostream>
#include <vector>

#include "structs/Token.h"

using namespace std;

class Tokenizer
{
public:
    vector<Token> tokenize(string &code);
};

#endif