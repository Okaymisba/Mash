#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
#include "Parser.h"
#include "func/readFile/readFile.h"
#include "func/hasCorrectExtension/hasCorrectExtension.h"

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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: ./mash <script.msh>" << endl;

        return 1;
    }

    string filePath = argv[1];

    if (!hasCorrectExtension(filePath, ".msh"))
    {
        cerr << "Error: The supplied file must have a .msh extension." << endl;
        return 1;
    }

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

    Parser parser(tokens);
    ASTNode ast = parser.parse();
    printAST(ast);

    cout << "\nUntill here" << endl;

    evaluator.evaluate(ast);

    return 0;
}
