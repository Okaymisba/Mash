#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
#include "Parser.h"
#include "func/readFile/readFile.h"

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
    string filePath = "SourceCode.txt";
    string code = readFile(filePath);
    cout << code << endl;


    Tokenizer tokenizer;
    Evaluator evaluator;

    vector<Token> tokens = tokenizer.tokenize(code);

    for (const auto &token : tokens)
    {
        cout << "Token Type: " << token.type << ", Token Value: " << token.value << endl;
    }

    cout << "\nIgnore below this: " << endl;
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
    cout << "\nUntill here" << endl;

    return 0;
}

