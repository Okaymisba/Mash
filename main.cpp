#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
#include "Parser.h"

using namespace std;

void printAST(const ASTNode &node, int indent = 0)
{
    for (int i = 0; i < indent; ++i)
        cout << "  ";
    cout << node.type;
    if (!node.value.empty())
        cout << " (" << node.value << ")";
    cout << endl;
    for (const auto &child : node.children)
    {
        printAST(child, indent + 1);
    }
}

int main()
{
    string code = R"( x= 'M')";

    Tokenizer tokenizer;
    Evaluator evaluator;

    vector<Token> tokens = tokenizer.tokenize(code);

    for (const auto &token : tokens)
    {
        cout << "Token Type: " << token.type << ", Token Value: " << token.value << endl;
    }

    cout << "\nIgnore bellow this: " << endl;
    try
    {
        Parser parser(tokens);
        ASTNode ast = parser.parse();
        printAST(ast);
    }
    catch (const runtime_error &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    cout << "Uptill here" << endl;

    return 0;
};
