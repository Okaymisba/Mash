#include "../../Evaluator.h"

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
    else
    {
        throw runtime_error("Undefined variable: " + identifier);
    }
}