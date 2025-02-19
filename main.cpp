#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
#include "Parser.h"
#include "func/readFile/readFile.h"
#include "func/hasCorrectExtension/hasCorrectExtension.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: mash <script.msh>" << endl;

        return 1;
    }

    string filePath = argv[1];

    if (!hasCorrectExtension(filePath, ".msh"))
    {
        cerr << "Error: The supplied file must have a .msh extension." << endl;
        return 1;
    }

    string code = readFile(filePath);

    Tokenizer tokenizer;
    Evaluator evaluator;

    vector<Token> tokens = tokenizer.tokenize(code);

    Parser parser(tokens);
    ASTNode ast = parser.parse();

    evaluator.evaluate(ast);

    return 0;
}
