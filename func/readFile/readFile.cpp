#include <fstream>
#include <sstream>
#include <iostream>
#include "readFile.h"

using namespace std;

string readFile(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return "";
    }

    stringstream buffer;
    char ch;
    while (file.get(ch))
    {
        if (ch == '\n')
        {
            buffer << "\\n";
        }
        else
        {
            buffer << ch;
        }
    }

    return buffer.str();
};