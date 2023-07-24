
#ifndef VARIABLE_FACTORY_H
#define VARIABLE_FACTORY_H

#include "..\keyword\keywordTrue.h"

extern const std::string NEWLINE_STRING;
extern const std::string QUOTE_STRING;

inline TypedProperty<int>* createNewInt(const std::string &value)
{
	Datatype rightHandType = gTypeChecker.getType(value);

	switch (rightHandType)
	{
	case TYPE_INT:
	{
		return new TypedProperty<int>("", 0, std::stoi(value));
	}
	}

	return nullptr;
}

inline TypedProperty<double>* createNewDouble(const std::string &value)
{
	Datatype rightHandType = gTypeChecker.getType(value);

	switch (rightHandType)
	{
	case TYPE_DOUBLE:
	{
		return new TypedProperty<double>("", 1, std::stod(value));
	}
	}

	return nullptr;
}

inline TypedProperty<std::string>* createNewString(std::string value)
{
	Datatype rightHandType = gTypeChecker.getType(value);

	switch (rightHandType)
	{
	case TYPE_STRING:
	{
		if (stringStartsWith(value, "\""))
			value = value.substr(1);
		if (stringEndsWith(value, "\""))
			value = value.substr(0, value.length() - 1);

		replaceAllSubstrings(value, "\\n", NEWLINE_STRING);
		replaceAllSubstrings(value, "\\\"", QUOTE_STRING);

		return new TypedProperty<std::string>("", 2, value);
	}
	}

	return nullptr;
}

inline TypedProperty<bool>* createNewBool(const std::string &value)
{
	Datatype rightHandType = gTypeChecker.getType(value);

	switch (rightHandType)
	{
	case TYPE_BOOL:
	{
		return createNewBoolFromString(value);
	}
	}

	return nullptr;
}

inline TypedProperty<int>* createNewIntFromConsole(const std::string &value)
{
	Datatype rightHandType = gTypeChecker.getTypeFromConsole(value);

	switch (rightHandType)
	{
	case TYPE_INT:
	{
		return new TypedProperty<int>("", 0, std::stoi(value));
	}
	}

	return nullptr;
}

inline TypedProperty<double>* createNewDoubleFromConsole(const std::string &value)
{
	Datatype rightHandType = gTypeChecker.getTypeFromConsole(value);

	switch (rightHandType)
	{
	case TYPE_DOUBLE:
	{
		return new TypedProperty<double>("", 1, std::stod(value));
	}
	}

	return nullptr;
}

inline TypedProperty<std::string>* createNewStringFromConsole(std::string value)
{
	Datatype rightHandType = gTypeChecker.getTypeFromConsole(value);

	switch (rightHandType)
	{
	case TYPE_STRING:
	{
		return new TypedProperty<std::string>("", 2, value);
	}
	}

	return nullptr;
}

inline TypedProperty<bool>* createNewBoolFromConsole(const std::string &value)
{
	Datatype rightHandType = gTypeChecker.getTypeFromConsole(value);

	switch (rightHandType)
	{
	case TYPE_BOOL:
	{
		return createNewBoolFromString(value);
	}
	}

	return nullptr;
}

#endif