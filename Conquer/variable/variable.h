
#ifndef VARIABLE_H
#define VARIABLE_H

#include "VariableFactory.h"
#include "..\core\function.h"
#include "keyword\keywordRead.h"
#include "..\operator\Operator.h"

const std::string EMPTY_STRING = "";

bool processVariableStatement(const std::string &variableName, const std::string &operatorString, std::string &rightHandValue, int arrayIndex = -1);

template <typename T>
inline void addTypedProperty(const std::string &statement, const int &datatype, T value)
{
	TypedProperty<T>* typedProperty = new TypedProperty<T>(statement, datatype, value);
	gStore->add(typedProperty);
}

template <typename T>
inline void addArray(const std::string &statement, const int &datatype, T value, const int &arraySize)
{
	Array<T>* myArray = new Array<T>(statement, datatype, value, arraySize);
	gStore->add(myArray);
}

void addTypedProperty(const std::string &statement, const std::string &datatype)
{
	Datatype type = DATATYPE_STRING_MAP.find(datatype)->second;
	
	switch (type)
	{
	case TYPE_INT:
	{
		addTypedProperty(statement, 0, 0);

		return;
	}
	case TYPE_DOUBLE:
	{
		addTypedProperty(statement, 1, 0.0);

		return;
	}
	case TYPE_STRING:
	{
		addTypedProperty(statement, 2, EMPTY_STRING);

		return;
	}
	case TYPE_BOOL:
	{
		addTypedProperty(statement, 3, false);

		return;
	}
	case TYPE_FILENAME:
	{
		addTypedProperty(statement, 4, EMPTY_STRING);
	
		return;
	}
	}
}

void addArray(const std::string &statement, const std::string &datatype, const int &arraySize)
{
	Datatype type = DATATYPE_STRING_MAP.find(datatype)->second;

	switch (type)
	{
	case TYPE_INT:
	{
		addArray(statement, 0, 0, arraySize);

		return;
	}
	case TYPE_DOUBLE:
	{
		addArray(statement, 1, 0.0, arraySize);

		return;
	}
	case TYPE_STRING:
	{
		addArray(statement, 2, EMPTY_STRING, arraySize);

		return;
	}
	case TYPE_BOOL:
	{
		addArray(statement, 3, false, arraySize);

		return;
	}
	case TYPE_FILENAME:
	{
		addArray(statement, 4, EMPTY_STRING, arraySize);

		return;
	}
	}
}

int getArrayIndexAndRemoveBrackets(std::string &statement)
{
	int leftBracket = statement.find_first_of("[");

	std::string arrayIndexString = statement.substr(leftBracket + 1, statement.length() - 1);
	statement = statement.substr(0, leftBracket);

	int arrayIndex = -1;

	try
	{
		arrayIndex = std::stoi(arrayIndexString);
	}
	catch (std::exception e)
	{
		arrayIndex = -1;
	}

	if (arrayIndex < 0)
	{
		Property *basicProperty = gStore->get(arrayIndexString);
		TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);
		arrayIndex = v->getValue();
	}

	return arrayIndex;
}

bool processVariableStatement(std::string &statement)
{
	std::string variableName = "";

	statement = gStore->removeVariableName(statement, variableName);
	Property *basicProperty = gStore->get(variableName);

	if (statement.find(">>") != std::string::npos)
	{
		TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
		executeReadFile(v, statement); 

		return false;
	}
	else if (statement.find("<<") != std::string::npos)
	{
		TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
		executeWriteFile(v, statement);

		return false;
	}
	// If we can find an open and close square bracket, we will add a new array
	else if (statement.find("[") != std::string::npos)
	{
		std::string origStatement = statement;

		// Get a substring... from the open square bracket (but not including it) to the end...
		std::string arrayIndexString = statement.substr(statement.find_first_of("[") + 1, statement.length());
		// And up to the closing square bracket (but not including it)
		arrayIndexString = arrayIndexString.substr(0, arrayIndexString.find_first_of("]"));

		// Get a substring... of what should be the operator and right hand side value
		statement = statement.substr(statement.find_first_of("]") + 1, statement.length());

		if (startsWithString(statement, OPERATOR_MAP))
		{
			int arrayIndex = -1;

			try
			{
				arrayIndex = std::stoi(arrayIndexString);
			}
			catch (std::exception e)
			{
			}

			if (arrayIndex < 0)
			{
				Property *basicProperty = gStore->get(arrayIndexString);
				TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);
				arrayIndex = v->getValue();
			}

			std::string operatorString = "";
			statement = removeStringFromMap(statement, OPERATOR_MAP, operatorString, MAXIMUM_OPERATOR_LENGTH);

			return processVariableStatement(variableName, operatorString, statement, arrayIndex);
		}
		else
		{
			statement = origStatement;
			
			std::string operatorString = "";
			statement = removeStringFromMap(statement, OPERATOR_MAP, operatorString, MAXIMUM_OPERATOR_LENGTH);
			
			origStatement = statement;

			// Get a substring... from the open square bracket (but not including it) to the end...
			std::string arrayIndexString = statement.substr(statement.find_first_of("[") + 1, statement.length());
			// And up to the closing square bracket (but not including it)
			arrayIndexString = arrayIndexString.substr(0, arrayIndexString.find_first_of("]"));

			// Get a substring... of what should be the operator and right hand side value
			statement = statement.substr(statement.find_first_of("]") + 1, statement.length());

			int arrayIndex = -1;

			try
			{
				arrayIndex = std::stoi(arrayIndexString);
			}
			catch (std::exception e)
			{
				arrayIndex = -1;
			}

			if (arrayIndex < 0)
			{
				Property *basicProperty = gStore->get(arrayIndexString);
				TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);
				arrayIndex = v->getValue();
			}

			statement = origStatement.substr(0, origStatement.find("["));

			return processVariableStatement(variableName, operatorString, statement, arrayIndex);
		}
	}
	else
	{
		if (stringStartsWith(statement, "."))
		{
			processFunctionCallOnVariable(basicProperty, statement);

			return false;
		}
		else
		{
			// Normal variable to process...
			std::string operatorString = "";
			statement = removeStringFromMap(statement, OPERATOR_MAP, operatorString, MAXIMUM_OPERATOR_LENGTH);

			return processVariableStatement(variableName, operatorString, statement);
		}
	}

	return false;
}

bool processVariableStatement(const std::string &variableName, const std::string &operatorString, std::string &rightHandValue, int arrayIndex)
{
	Property *basicProperty = gStore->get(variableName);
	Property *rightHandProperty = gStore->get(rightHandValue);

	if (rightHandProperty != nullptr)
	{
		if (arrayIndex >= 0)
		{
			if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
			{
				Array<int>* vRight = dynamic_cast<Array<int>*>(rightHandProperty);

				return executeOperator(vRight, operatorString, v, arrayIndex, true);
			}
			else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
			{
				Array<double>* vRight = dynamic_cast<Array<double>*>(rightHandProperty);

				return executeOperator(vRight, operatorString, v, arrayIndex, true);
			}
			else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty <std::string>*>(basicProperty))
			{
				Array<std::string>* vRight = dynamic_cast<Array<std::string>*>(rightHandProperty);

				return executeOperator(vRight, operatorString, v, arrayIndex, true);
			}
			else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
			{
				Array<bool>* vRight = dynamic_cast<Array<bool>*>(rightHandProperty);

				return executeOperator(vRight, operatorString, v, arrayIndex, true);
			}
			else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
			{
				TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightHandProperty);

				return executeOperator(v, operatorString, vRight, arrayIndex);
			}
			else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
			{
				TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightHandProperty);

				return executeOperator(v, operatorString, vRight, arrayIndex);
			}
			else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
			{
				TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightHandProperty);

				return executeOperator(v, operatorString, vRight, arrayIndex);
			}
			else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
			{
				TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(rightHandProperty);

				return executeOperator(v, operatorString, vRight, arrayIndex);
			}
		}
		else if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
		{
			TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightHandProperty);

			return executeOperator(v, operatorString, vRight);
		}
		else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
		{
			TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightHandProperty);

			return executeOperator(v, operatorString, vRight);
		}
		else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
		{
			TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightHandProperty);

			return executeOperator(v, operatorString, vRight);
		}
		else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
		{
			TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(rightHandProperty);

			return executeOperator(v, operatorString, vRight);
		}
	}
	else
	{
		bool result;
		Datatype type = gTypeChecker.getType(rightHandValue);

		switch (type)
		{
		case TYPE_INT:
		{
			rightHandProperty = createNewInt(rightHandValue);

			break;
		}
		case TYPE_DOUBLE:
		{
			rightHandProperty = createNewDouble(rightHandValue);

			break;
		}
		case TYPE_STRING:
		{
			rightHandProperty = createNewString(rightHandValue);

			break;
		}
		case TYPE_BOOL:
		{
			rightHandProperty = createNewBool(rightHandValue);

			break;
		}
		}

		if (arrayIndex >= 0)
		{
			if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
			{
				Array<int>* vRight = dynamic_cast<Array<int>*>(rightHandProperty);

				result = executeOperator(vRight, operatorString, v, arrayIndex, true);

				delete rightHandProperty;
				return result;
			}
			else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
			{
				Array<double>* vRight = dynamic_cast<Array<double>*>(rightHandProperty);

				result = executeOperator(vRight, operatorString, v, arrayIndex, true);

				delete rightHandProperty;
				return result;
			}
			else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty <std::string>*>(basicProperty))
			{
				Array<std::string>* vRight = dynamic_cast<Array<std::string>*>(rightHandProperty);

				result = executeOperator(vRight, operatorString, v, arrayIndex, true);

				delete rightHandProperty;
				return result;
			}
			else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
			{
				Array<bool>* vRight = dynamic_cast<Array<bool>*>(rightHandProperty);

				result = executeOperator(vRight, operatorString, v, arrayIndex, true);

				delete rightHandProperty;
				return result;
			}
			else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
			{
				TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightHandProperty);

				result = executeOperator(v, operatorString, vRight, arrayIndex);

				delete rightHandProperty;
				return result;
			}
			else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
			{
				TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightHandProperty);

				result = executeOperator(v, operatorString, vRight, arrayIndex);

				delete rightHandProperty;
				return result;
			}
			else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
			{
				TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightHandProperty);

				result = executeOperator(v, operatorString, vRight, arrayIndex);

				delete rightHandProperty;
				return result;
			}
			else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
			{
				TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(rightHandProperty);

				result = executeOperator(v, operatorString, vRight, arrayIndex);

				delete rightHandProperty;
				return result;
			}
		}
		else if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
		{
			TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightHandProperty);

			result = executeOperator(v, operatorString, vRight);

			delete rightHandProperty;
			return result;
		}
		else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
		{
			TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightHandProperty);

			result = executeOperator(v, operatorString, vRight);

			delete rightHandProperty;
			return result;
		}
		else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
		{
			TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightHandProperty);

			result = executeOperator(v, operatorString, vRight);

			delete rightHandProperty;
			return result;
		}
		else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
		{
			TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(rightHandProperty);

			result = executeOperator(v, operatorString, vRight);

			delete rightHandProperty;
			return result;
		}
	}
	
	return false;
}

#endif