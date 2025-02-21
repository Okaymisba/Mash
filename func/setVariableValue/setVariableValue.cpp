#include "../../Evaluator.h"

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