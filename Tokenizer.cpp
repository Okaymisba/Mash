#include <iostream>
#include "Tokenizer.h"
#include <map>
#include <regex>

vector<Token> Tokenizer::tokenize(string &input)
{
    // Map of all the tokens
    vector<pair<string, string>> patterns = {
        {"PRINT", R"(\bprint\b)"},
        {"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"},
        {"NUMBER", R"(\d+)"},
        {"ASSIGN", R"(=)"},
        {"PLUS", R"(\+)"},
        {"SEMICOLON", R"(;)"},
        {"WHITESPACE", R"(\s+)"},
        {"STRING", R"(".*?")"},
        {"CHAR", R"('([a-zA-Z])')"},
    };

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
