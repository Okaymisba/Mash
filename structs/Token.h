#include <string>
#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

struct Token
{
    string type;
    string value;

    Token(const string &t, const string &v) : type(t), value(v) {}
};

#endif