#include <fstream>
#include <sstream>
#include <iostream>
#include "readFile.h"

using namespace std;

/**
 * Reads the content of a file and returns it as a string.
 *
 * This function opens a file specified by the file path, reads its content,
 * and constructs a string while preserving actual newlines (`\n`).
 * If the file cannot be opened, it outputs an error message to standard error
 * and exits with an error code.
 *
 * @param filePath The path to the file to be read.
 * @return A string containing the contents of the file with actual newlines.
 */

string readFile(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filePath << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << file.rdbuf(); // Reads the file as-is, preserving actual newlines

    return buffer.str();
}
