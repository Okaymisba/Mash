#include <iostream>
#include "Tokenizer.h"
#include <map>
#include <regex>

vector<Token> Tokenizer::tokenize(string &input)
{
    // Map of all the tokens
    vector<pair<string, string>> patterns = {
        {"CHECK_IF", R"(\bcheck\s*if\b)"},
        {"ELSE", R"(\belse\b)"},
        {"ELSE IF", R"(\s+\belse\s+if\b)"},
        {"PRINT", R"(\bprint\b)"},
        {"FOR", R"(\bfor\b)"},
        {"WHILE", R"(\bwhile\b)"},
        {"LINE_BREAK", R"(\\n)"},
        {"BOOL", R"(\b(?:True|False|bool)\b)"},
        {"DOUBLE", R"(\b(?:double|\d+\.\d{8,})\b)"},
        {"DOUBLE", R"([+-]\d+\.\d{8,})"},
        {"FLOAT", R"(\b(?:float|\d+\.\d{1,7})\b)"},
        {"FLOAT", R"([+-]\d+\.\d{1,7})"},
        {"INTEGER", R"(\b(?:int|\d+)\b)"},
        {"INTEGER", R"([+-]\d+)"},
        {"STRING", R"("[^"]*")"},
        {"CHAR", R"('[^']')"},
        {"COMPARISON_OPERATOR", R"(==|!=|<=|>=|<|>)"},
        {"ASSIGNMENT_OPERATOR", R"(\+=|\-=|/=|\*=|\%=)"},
        {"ASSIGN", R"(=)"},
        {"ARITHMETIC_OPERATOR", R"([+\*/%-])"},
        {"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"},
        {"SEMICOLON", R"(;)"},
        {"COLON", R"(:)"},
        {"DOT", R"(\.)"},
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
                    if(key == "STRING" || key == "CHAR"){
                        string str = match[i + 1];
                        string string_text = str.substr(1,str.length()-2);
                        tokens.emplace_back(key,string_text);
                    }
                    else{
                        tokens.emplace_back(key, match[i + 1].str());
                    }
                }
            }
        }

        // Move searchStart to the next unmatched position
        searchStart = match.suffix().first;
    }

    return tokens;
}
