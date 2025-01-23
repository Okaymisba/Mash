#include <iostream>
#include "Tokenizer.h"
#include <map>
#include <regex>

vector<token> Tokenizer::tokenize(string &input)
{
    vector<pair<string, string>> patterns = {
        {"LET", "\\blet\\b"},
        {"IDENTIFIER", "[a-zA-Z_][a-zA-Z0-9_]*"},
        {"PRINT", "\\bprint\\b"},
        {"NUMBER", "\\d+"},
        {"ASSIGN", "="},
        {"PLUS", "\\+"},
        {"SEMICOLON", ";"},
        {"WHITESPACE", "\\s+"}};

    // Build regex pattern for all tokens
    string regexString;
    for (size_t i = 0; i < patterns.size(); ++i)
    {
        if (!regexString.empty())
            regexString += "|";
        regexString += "(" + patterns[i].second + ")";
    }
    regex regexPattern(regexString);

    smatch match;
    vector<token> tokens;

    string::const_iterator searchStart(input.cbegin());
    while (regex_search(searchStart, input.cend(), match, regexPattern))
    {

        for (size_t i = 0; i < patterns.size(); ++i)
        {
            if (match[i + 1].matched)
            {
                string &key = patterns[i].first;

                if (key != "WHITESPACE")

                    tokens.emplace_back(key, match[i + 1].str());
            }
        }
        searchStart = match.suffix().first;
    }

    return tokens;
}
