#include <string>
#include <iostream>
#include <vector>
#ifndef TOKENIIZER_H
#define TOKENIZER_H

using namespace std;

struct token
{
    string type;
    string value;

    token(const string& t, const string& v) : type(t), value(v) {}
};

class Tokenizer
{
public:
    vector<token> tokenize(string &code);
};

#endif