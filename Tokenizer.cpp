#include "Tokenizer.h"
#include <iostream>
#include <map>
#include <regex>
#include <climits>

using namespace std;

vector<Token> Tokenizer::tokenize(const string &input)
{
    vector<pair<string, string>> patterns = {
        {"WHITESPACE", R"([ \t\r]+)"},
        {"NEWLINE", R"(\n)"},
        {"COMMENT", R"(//[^\n]*)"},
        {"COLON", R"(:)"},
        {"COMPARISON_OPERATOR", R"(==|!=|<=|>=|<|>)"},
        {"ASSIGN", R"(=)"},
        {"ARITHMETIC_OPERATOR", R"([-+*/%])"},
        {"OPEN_ROUND_BRACKET", R"(\()"},
        {"CLOSE_ROUND_BRACKET", R"(\))"},
        {"OPEN_CURLY_BRACKET", R"(\{)"},
        {"CLOSE_CURLY_BRACKET", R"(\})"},
        {"SEMICOLON", R"(;)"},
        {"CHECK_IF", R"(\bcheck[ \t]+if\b)"},
        {"ELSE_IF", R"(\belse[ \t]+if\b)"},
        {"ELSE", R"(\belse\b)"},
        {"FOR", R"(\bfor\b)"},
        {"IN", R"(\bin\b)"},
        {"TO", R"(\bto\b)"},
        {"STEP", R"(\bstep\b)"},
        {"UNTIL", R"(\buntil\b)"},
        {"DOWNTO", R"(\bdownto\b)"},
        {"DOWNUNTIL", R"(\bdownuntil\b)"},
        {"WHILE", R"(\bwhile\b)"},
        {"PRINT", R"(\bprint\b)"},
        {"BOOL", R"(\btrue\b|\bfalse\b)"},
        {"CHAR", R"('(?:[^'\\]|\\.)')"},
        {"STRING", R"("(?:[^"\\]|\\.)*")"},
        {"FLOAT", R"(\b\d+\.\d+f\b)"},
        {"DOUBLE", R"(\b\d+\.\d+\b)"},
        {"INTEGER", R"(\b\d+\b)"},
        {"TYPE", R"(\bint\b|\bfloat\b|\bdouble\b|\blong\b|\bbool\b|\bstring\b|\bchar\b)"},
        {"IDENTIFIER", R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)"}};

    string regexString;
    for (size_t i = 0; i < patterns.size(); ++i)
    {
        if (i > 0)
            regexString += "|";
        regexString += "(" + patterns[i].second + ")";
    }

    regex regexPattern(regexString);
    smatch match;
    vector<Token> tokens;
    string::const_iterator searchStart(input.cbegin());

    string lastType = "";

    while (regex_search(searchStart, input.cend(), match, regexPattern))
    {
        for (size_t i = 0; i < patterns.size(); ++i)
        {
            if (match[i + 1].matched)
            {
                string type = patterns[i].first;
                string value = match[i + 1].str();

                if (type == "WHITESPACE" || type == "COMMENT")
                    break;
                if (type == "NEWLINE")
                {
                    tokens.emplace_back("LINE_BREAK", "\\n");
                    break;
                }

                if (type == "TYPE")
                {
                    lastType = value;
                }

                if (type == "INTEGER")
                {
                    long long numValue = stoll(value);

                    if (lastType == "long")
                    {
                        type = "LONG";
                    }
                    else if (numValue > INT_MAX)
                    {
                        type = "LONG";
                    }
                    else
                    {
                        type = "INTEGER";
                    }
                }
                else if (type == "DOUBLE" && lastType == "float")
                {
                    type = "FLOAT";
                }
                else if (type == "STRING" && lastType == "char")
                {
                    type = "CHAR";
                }
                else if (type == "FLOAT")
                {

                    if (!value.empty() && value.back() == 'f')
                    {
                        value.pop_back();
                    }
                }

                tokens.emplace_back(type, value);
                break;
            }
        }
        searchStart = match.suffix().first;
    }

    tokens.emplace_back("EOF", "");
    return tokens;
}