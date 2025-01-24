#include <iostream>
#include "Tokenizer.h"
#include <map>
#include <regex>

vector<token> Tokenizer::tokenize(string &input)
{
    vector<pair<string, string>> patterns = {
        {"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"},
        {"PRINT", R"(\bprint\b)"},
        {"NUMBER", R"(\d+)"},
        {"ASSIGN", R"(=)"},
        {"PLUS", R"(\+)"},
        {"SEMICOLON", R"(;)"},
        {"WHITESPACE", R"(\s+)"},
        {"STRING", R"("[a-zA-Z]")"},
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

    // Debugging regex string creation
    cout << "Constructed Regex Pattern: " << regexString << endl;

    regex regexPattern(regexString);
    smatch match;
    vector<token> tokens;

    string::const_iterator searchStart(input.cbegin());

    while (regex_search(searchStart, input.cend(), match, regexPattern))
    {
        // Debugging matched groups
        cout << "Matched Text: " << match.str(0) << endl;

        for (size_t i = 0; i < patterns.size(); ++i)
        {
            cout << match[i + 1].matched << endl;
            if (match[i + 1].matched)
            {
                string &key = patterns[i].first;

                // Print matched token type and value
                cout << "Matched Type: " << key << ", Value: " << match[i + 1].str() << endl;

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
