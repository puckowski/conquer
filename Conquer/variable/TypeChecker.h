
#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H

class TypeChecker
{
private:
	template <typename T>
	inline bool is(const std::string& s)
	{
		std::istringstream iss(s);
		T x;
		char c;

		return iss >> x && !(iss >> c);
	}

	inline bool TypeChecker::isInteger(const std::string &text)
	{
		if (text.empty() || ((!isdigit(text[0])) && (text[0] != '-') && (text[0] != '+')))
			return false;

		char *p;
		strtol(text.c_str(), &p, 10);

		return (*p == 0);
	}

protected:

public:
	TypeChecker::TypeChecker()
	{
	}

	TypeChecker::~TypeChecker()
	{
	}

	Datatype TypeChecker::getType(Property *basicProperty)
	{
		int typeString = basicProperty->getType();

		if (typeString == DATATYPE_INT_MAP.find(TYPE_INT)->second)
			return TYPE_INT;
		else if (typeString == DATATYPE_INT_MAP.find(TYPE_DOUBLE)->second)
			return TYPE_DOUBLE;
		else if (typeString == DATATYPE_INT_MAP.find(TYPE_STRING)->second)
			return TYPE_STRING;
		else if (typeString == DATATYPE_INT_MAP.find(TYPE_BOOL)->second)
			return TYPE_BOOL;

		return TYPE_UNKNOWN;
	}

	Datatype TypeChecker::getType(const std::string &text)
	{
		if (stringStartsWith(text, "\""))
			return TYPE_STRING;
		else if (text.find(".") != std::string::npos)
			return TYPE_DOUBLE;
		else if (text == "true" || text == "false")
			return TYPE_BOOL;
		else if (isInteger(text))
			return TYPE_INT;
		else
			return TYPE_UNKNOWN;
	}

	Datatype TypeChecker::getTypeFromConsole(const std::string &text)
	{
		if (is<double>(text) && text.find(".") != std::string::npos)
			return TYPE_DOUBLE;
		else if (text == "true" || text == "false")
			return TYPE_BOOL;
		else if (isInteger(text))
			return TYPE_INT;
		else
			return TYPE_STRING;

		return TYPE_UNKNOWN;
	}
};

#endif