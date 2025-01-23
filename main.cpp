#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
#include "Parser.h"

using namespace std;

int main()
{
    string code = "let x =5;";

    Tokenizer tokenizer;
    Evaluator evaluator;
    Parser parser;

    vector<token> tokens = tokenizer.tokenize(code);

    for (const auto &token : tokens)
    {
        cout << "Token Type: " << token.type << ", Token Value: " << token.value << endl;
    }

    return 0;
};
