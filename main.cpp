#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
#include "Parser.h"
#include "func/readFile/readFile.h"
#include "func/hasCorrectExtension/hasCorrectExtension.h"
#include <sstream>
#include <fstream>

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

string Parser::toString(const ASTNode &node, int indent) const
{
    ostringstream oss;
    string pad(indent * 2, ' ');

    oss << pad << node.type;
    if (!node.value.empty())
        oss << " (" << node.value << ")";
    oss << "\n";

    for (const auto &child : node.children)
    {
        oss << toString(child, indent + 1);
    }
    return oss.str();
}

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

    ofstream tokensfile;
    tokensfile.open("tokens.txt");

    for (const auto &token : tokens)
    {
        tokensfile << "Token Type: " << token.type << ", Token Value: " << token.value << endl;
    }
    tokensfile.close();

    Parser parser(tokens);
    ASTNode ast = parser.parse();

    ofstream astfile;
    astfile.open("ast.txt");
    astfile << parser.toString(ast);
    astfile.close();

    evaluator.evaluate(ast);

    return 0;
}