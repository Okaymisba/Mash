#include "../../Parser.h"
using namespace std;

bool Parser::ValidateDataType(const ASTNode& node1,const ASTNode& node2){
    if ((node1.children[0].value == "int") && (node2.type == "INTEGER"))
    {
        return true;
    }
    else if ((node1.children[0].value == "bool") && (node2.type == "BOOL")){
        return true;
    }
    else if ((node1.children[0].value == "double") && (node2.type == "DOUBLE")){
        return true;
    }
    else if ((node1.children[0].value == "string") && (node2.type == "STRING")){
        return true;
    }
    else if ((node1.children[0].value == "char") && (node2.type == "CHAR")){
        return true;
    }
    else if ((node1.children[0].value == "float") && (node2.type == "FLOAT")){
        return true;
    }
    else if ((node1.children[0].value == "long") && (node2.type == "LONG")){
        return true;
    }
    else
        return false;
}


