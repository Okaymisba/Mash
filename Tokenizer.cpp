#include "Tokenizer.h"
#include <iostream>
#include <map>
#include <regex>

using namespace std;

vector<Token> Tokenizer::tokenize(const string &input) {
    vector<pair<string, string>> patterns = {
        {"WHITESPACE", R"([ \t\r]+)"}, // Ignore whitespace
        {"NEWLINE", R"(\n)"},          // Preserve line breaks
        {"COMMENT", R"(//[^\n]*)"},    // ✅ Ignore comments (everything after //)
        {"CHECK_IF", R"(\bcheck[ \t]+if\b)"},
        {"ELSE_IF", R"(\belse[ \t]+if\b)"},  // ✅ ELSE_IF separately
        {"ELSE", R"(\belse\b)"},
        {"FOR", R"(\bfor\b)"},          // ✅ For loop
        {"TO", R"(\bto\b)"},            // ✅ For loop range keyword
        {"STEP", R"(\bstep\b)"},        // ✅ Step keyword for for-loops
        {"UPTO", R"(\bupto\b)"},        // ✅ Upto range keyword
        {"DOWNTO", R"(\bdownto\b)"},    // ✅ Downto range keyword
        {"UPTILL", R"(\buptill\b)"},    // ✅ Uptill range keyword
        {"DOWNTILL", R"(\bdowntill\b)"},// ✅ Downtill range keyword
        {"DOWNUNTIL", R"(\bdownuntil\b)"}, // ✅ Downuntil range keyword
        {"WHILE", R"(\bwhile\b)"},      // ✅ Added WHILE as separate token
        {"PRINT", R"(\bprint\b)"},
        {"BOOL", R"(\bTrue\b|\bFalse\b)"},
        {"STRING", R"("(?:[^"\\]|\\.)*")"},
        {"FLOAT", R"(\b\d+\.\d+f\b)"}, // ✅ Float with 'f' suffix
        {"DOUBLE", R"(\b\d+\.\d+\b)"}, // ✅ Double without 'f'
        {"INTEGER", R"(\b\d+\b)"},
        {"COMPARISON_OPERATOR", R"(==|!=|<=|>=|<|>)"},
        {"ASSIGN", R"(=)"},
        {"ARITHMETIC_OPERATOR", R"([-+*/%])"},
        {"OPEN_ROUND_BRACKET", R"(\()"},
        {"CLOSE_ROUND_BRACKET", R"(\))"},
        {"OPEN_CURLY_BRACKET", R"(\{)"},
        {"CLOSE_CURLY_BRACKET", R"(\})"},
        {"SEMICOLON", R"(;)"},
        {"IDENTIFIER", R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)"}  // ✅ No conflicts with keywords
    };

    string regexString;
    for (size_t i = 0; i < patterns.size(); ++i) {
        if (i > 0) regexString += "|";
        regexString += "(" + patterns[i].second + ")";
    }

    regex regexPattern(regexString);
    smatch match;
    vector<Token> tokens;
    string::const_iterator searchStart(input.cbegin());

    while (regex_search(searchStart, input.cend(), match, regexPattern)) {
        for (size_t i = 0; i < patterns.size(); ++i) {
            if (match[i + 1].matched) {
                string type = patterns[i].first;

                if (type == "WHITESPACE") break; // Ignore whitespace
                if (type == "COMMENT") break;    // ✅ Ignore comments
                if (type == "NEWLINE") {
                    tokens.emplace_back("LINE_BREAK", "\\n");
                    break;
                }

                tokens.emplace_back(type, match[i + 1].str());
                break;
            }
        }
        searchStart = match.suffix().first;
    }

    tokens.emplace_back("EOF", "");
    return tokens;
}
