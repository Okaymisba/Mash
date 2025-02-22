#include <iostream>
#include "Tokenizer.h"
#include <map>
#include <regex>

vector<Token> Tokenizer::tokenize(string &input)
{
    vector<pair<string, string>> patterns = {
        // Symbols first (to prevent misparsing)
        {"OPEN_ROUND_BRACKET", R"(\()"},
        {"CLOSE_ROUND_BRACKET", R"(\))"},
        {"OPEN_CURLY_BRACKET", R"(\{)"},
        {"CLOSE_CURLY_BRACKET", R"(\})"},
        {"SEMICOLON", R"(;)"},
        {"COLON", R"(:)"},
        {"DOT", R"(\.)"},

        // Keywords 
        {"FOR", R"(\bfor\b)"},
        {"TO", R"(\bto\b)"},
        {"CHECK_IF", R"(\bcheck\s*if\b)"},
        {"ELSE", R"(\belse\b)"},
        {"ELSE IF", R"(\belse\s+if\b)"},
        {"PRINT", R"(\bprint\b)"},
        {"WHILE", R"(\bwhile\b)"},
        {"BOOL", R"(\b(True|False)\b)"},

        // Literals
        {"LINE_BREAK", R"(\n)"},
        {"DOUBLE", R"(\d+\.\d{8,})"},
        {"FLOAT", R"(\d+\.\d{1,7})"},
        {"INTEGER", R"(\d+)"},
        {"STRING", R"("[^"]*")"},
        {"CHAR", R"('[^']')"},

        // Operators (ordered by precedence)
        {"ASSIGNMENT_OPERATOR", R"(\+=|\-|\/=|\*=|\%=)"},
        {"COMPARISON_OPERATOR", R"(==|!=|<=|>=|<|>)"},
        {"ARITHMETIC_OPERATOR", R"([+*\/%-])"},
        {"ASSIGN", R"(=)"},

        // Identifier (last)
        {"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"}
    };

    // Build regex pattern
    string regexString;
    for (const auto& pair : patterns) {
        if (!regexString.empty()) regexString += "|";
        regexString += "(" + pair.second + ")";
    }

    regex regexPattern(regexString);
    smatch match;
    vector<Token> tokens;

    string::const_iterator searchStart(input.cbegin());

    while (regex_search(searchStart, input.cend(), match, regexPattern)) {
        for (size_t i = 0; i < patterns.size(); ++i) {
            if (match[i+1].matched) {
                string type = patterns[i].first;
                string value = match[i+1].str();

                // Handle special cases
                if (type == "STRING" || type == "CHAR") {
                    tokens.emplace_back(type, value.substr(1, value.length()-2));
                } else {
                    tokens.emplace_back(type, value);
                }
                break;
            }
        }
        searchStart = match.suffix().first;
    }

    tokens.emplace_back("EOF", "");
    return tokens;
}