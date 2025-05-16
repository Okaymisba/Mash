#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <vector>

using namespace std;

struct ASTNode
{
    string type;
    string value;
    vector<ASTNode> children;

    // Default constructor
    ASTNode() : type(""), value("") {}

    // Parameterized constructor
    ASTNode(const string &type, const string &value = "") : type(type), value(value) {}
};

#endif