#include <fstream>
#include <sstream>
#include <iostream>
#include "readFile.h"

using namespace std;

/**
 * Reads the content of a file and returns it as a string.
 *
 * This function opens a file specified by the file path, reads its content,
 * and constructs a string. It replaces newline characters with the literal
 * string "\n" to preserve line breaks in a single line string format.
 * If the file cannot be opened, it outputs an error message to standard error
 * and returns an empty string.
 *
 * @param filePath The path to the file to be read.
 * @return A string containing the contents of the file with newline characters
 *         replaced by "\n". Returns an empty string if the file cannot be opened.
 */

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