#include <string>
#include <vector>
#ifndef ASTNODE_H
#define ASTNODE_H

using namespace std;

struct ASTNode
{
    string type;
    string value;
    vector<ASTNode> children;

    ASTNode(const string &type, const string &value = "") : type(type), value(value) {}
};


#endif