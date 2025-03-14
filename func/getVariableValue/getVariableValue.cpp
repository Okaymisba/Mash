#include "../../Evaluator.h"

/**
 * Retrieves the value of a variable as a string.
 * The variable type is determined by searching each of the type-specific maps.
 * If the variable is not found in any of the maps, a runtime error is thrown.
 *
 * @param identifier The variable name to retrieve.
 * @return The value of the variable as a string.
 * @throws runtime_error If the variable is not found.
 */

string Evaluator::getVariableValue(const string &identifier)
{
    if (intVariables.find(identifier) != intVariables.end())
    {
        return to_string(intVariables[identifier]);
    }
    else if (floatVariables.find(identifier) != floatVariables.end())
    {
        return to_string(floatVariables[identifier]);
    }
    else if (doubleVariables.find(identifier) != doubleVariables.end())
    {
        return to_string(doubleVariables[identifier]);
    }
    else if (boolVariables.find(identifier) != boolVariables.end())
    {
        return boolVariables[identifier] ? "true" : "false";
    }
    else if (stringVariables.find(identifier) != stringVariables.end())
    {
        return stringVariables[identifier];
    }
    else if (charVariables.find(identifier) != charVariables.end())
    {
        return string(1, charVariables[identifier]);
    }
    else if (longVariables.find(identifier) != longVariables.end())
    {
        return to_string(longVariables[identifier]);
    }
    else
    {
        throw runtime_error("Undefined variable: " + identifier);
    }
}