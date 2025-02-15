#include "hasCorrectExtension.h"
#include <string>

using namespace std;

/**
 * Checks whether the given file path has the given extension.
 *
 * @param filePath The path to the file to be checked.
 * @param extension The extension to be checked.
 * @return true if the file has the extension; false otherwise.
 */

bool hasCorrectExtension(const string &filePath, const string &extension)
{
    if (filePath.length() < extension.length() + 1)
    {
        return false;
    }

    return filePath.substr(filePath.length() - extension.length()) == extension;
}