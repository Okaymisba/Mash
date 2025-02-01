#include <iostream>
#include "Tokenizer.h"
#include <map>
#include <regex>

vector<Token> Tokenizer::tokenize(string &input)
{
    // Map of all the tokens
    vector<pair<string, string>> patterns = {
        {"IF", R"(\bif\b)"},
        {"WHILE", R"(\bwhile\b)"},
        {"FOR", R"(\bfor\b)"},
        {"PRINT", R"(\bprint\b)"},
        {"LINE_BREAK", R"(\\n)"},
        {"BOOL", R"(\bTrue\b)"},
        {"BOOL", R"(\bFalse\b)"},
        {"FLOAT", R"(\bfloat\b)"},
        {"INTEGER", R"(\bint\b)"},
        {"STRING", R"("[^"]*")"},
        {"CHAR", R"('[^']')"},
        {"COMPARISON_OPERATOR", R"(==|!=|<=|>=|<|>)"},
        {"ASSIGN", R"(=)"},
        {"ARITHMETIC_OPERATOR", R"([+\*/\-])"},
        {"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"},
        {"WHITESPACE", R"(\s*)"},
        {"NUMBER", R"(\d+)"},
        {"SEMICOLON", R"(;)"},
        {"OPEN_ROUND_BRACKET", R"(\()"},
        {"CLOSE_ROUND_BRACKET", R"(\))"},
        {"OPEN_CURLY_BRACKET", R"(\{)"},
        {"CLOSE_CURLY_BRACKET", R"(\})"},
        {"OPEN_SQUARE_BRACKET", R"(\[)"},
        {"CLOSE_SQUARE_BRACKET", R"(\])"}};

    // Constructing a single regex pattern from all token patterns
    string regexString;
    for (size_t i = 0; i < patterns.size(); ++i)
    {
        if (!regexString.empty())
            regexString += "|";
        regexString += "(" + patterns[i].second + ")";
    }

    regex regexPattern(regexString);
    smatch match;
    vector<Token> tokens;

    string::const_iterator searchStart(input.cbegin());

    while (regex_search(searchStart, input.cend(), match, regexPattern))
    {

        for (size_t i = 0; i < patterns.size(); ++i)
        {
            if (match[i + 1].matched)
            {
                string &key = patterns[i].first;

                if (key != "WHITESPACE")
                {
                    tokens.emplace_back(key, match[i + 1].str());
                }
            }
        }

        // Move searchStart to the next unmatched position
        searchStart = match.suffix().first;
    }

    return tokens;
}
