#include "../../Evaluator.h"

/**
 * Sets the value of a variable in the appropriate type-specific map.
 *
 * This function assigns the given value to a variable identified by the
 * specified identifier, converting the value to the appropriate type based
 * on the provided type string. The function supports the following types:
 * "INTEGER", "FLOAT", "DOUBLE", "BOOL", and "STRING".
 *
 * @param identifier The name of the variable to set.
 * @param value The value to be set for the variable, as a string.
 * @param type A string representing the type of the variable. Must be one
 *             of "INTEGER", "FLOAT", "DOUBLE", "BOOL", or "STRING".
 * @throws runtime_error If the provided type is unsupported.
 */

void Evaluator::setVariableValue(const string &identifier, const string &value, const string &type)
{
    if (type == "INTEGER")
    {
        intVariables[identifier] = stoi(value);
    }
    else if (type == "FLOAT")
    {
        floatVariables[identifier] = stof(value);
    }
    else if (type == "DOUBLE")
    {
        doubleVariables[identifier] = stod(value);
    }
    else if (type == "BOOL")
    {
        boolVariables[identifier] = (value == "true");
    }
    else if (type == "STRING")
    {
        stringVariables[identifier] = value;
    }
    else
    {
        throw runtime_error("Unsupported variable type: " + type);
    }
}