
#ifndef OPERATOR_H
#define OPERATOR_H

const int MAXIMUM_OPERATOR_LENGTH = 2;

const std::string NEWLINE_STRING = std::string("\n");
const std::string QUOTE_STRING   = std::string("\"");

enum Operator
{
	OPERATOR_ASSIGN,
	OPERATOR_PLUS_EQUAL,
	OPERATOR_MINUS_EQUAL,
	OPERATOR_MUL_EQUAL,
	OPERATOR_DIV_EQUAL,
	OPERATOR_POW_EQUAL,
	OPERATOR_COMPARE,
	OPERATOR_LESS_THAN,
	OPERATOR_LESS_THAN_OR_EQUAL,
	OPERATOR_GREATER_THAN,
	OPERATOR_GREATER_THAN_OR_EQUAL,
	OPERATOR_NOT_EQUAL,
	OPERATOR_OUTPUT,
	OPERATOR_INPUT,
	OPERATOR_DOT
};

const std::map<Operator, std::string> OPERATOR_MAP =
{
	{ OPERATOR_ASSIGN,                "="  },
	{ OPERATOR_PLUS_EQUAL,            "+=" },
	{ OPERATOR_MINUS_EQUAL,           "-=" },
	{ OPERATOR_MUL_EQUAL,             "*=" },
	{ OPERATOR_DIV_EQUAL,             "/=" },
	{ OPERATOR_POW_EQUAL,             "^=" },
	{ OPERATOR_COMPARE,               "==" },
	{ OPERATOR_LESS_THAN,             "<"  },
	{ OPERATOR_LESS_THAN_OR_EQUAL,    "<=" },
	{ OPERATOR_GREATER_THAN,          ">"  },
	{ OPERATOR_GREATER_THAN_OR_EQUAL, ">=" },
	{ OPERATOR_NOT_EQUAL,             "!=" },
	{ OPERATOR_OUTPUT,                "<<" },
	{ OPERATOR_INPUT,                 ">>" },
	{ OPERATOR_DOT,                    "." }
};

const std::map<std::string, Operator> OPERATOR_STRING_MAP =
{
	{ "=",  OPERATOR_ASSIGN                },
	{ "+=", OPERATOR_PLUS_EQUAL            },
	{ "-=", OPERATOR_MINUS_EQUAL           },
	{ "*=", OPERATOR_MUL_EQUAL             },
	{ "/=", OPERATOR_DIV_EQUAL             },
	{ "^=", OPERATOR_POW_EQUAL             },
	{ "==", OPERATOR_COMPARE               },
	{ "<",  OPERATOR_LESS_THAN             },
	{ "<=", OPERATOR_LESS_THAN_OR_EQUAL    },
	{ ">",  OPERATOR_GREATER_THAN          },
	{ ">=", OPERATOR_GREATER_THAN_OR_EQUAL },
	{ "!=", OPERATOR_NOT_EQUAL             },
	{ "<<", OPERATOR_OUTPUT                },
	{ ">>", OPERATOR_INPUT                 },
	{ ".",  OPERATOR_DOT                   }
};

template <typename T>
bool executeOperator(TypedProperty<T> *leftProperty, const std::string &operatorString, TypedProperty<T> *rightProperty)
{
	Operator op = OPERATOR_STRING_MAP.find(operatorString)->second;

	switch (op)
	{
	case OPERATOR_ASSIGN:
	{
		executeAssignOperator(leftProperty, rightProperty);

		return false;
	}
	case OPERATOR_COMPARE:
	{
		return checkEquals(leftProperty, rightProperty);
	}
	case OPERATOR_NOT_EQUAL:
	{
		return checkNotEquals(leftProperty, rightProperty);
	}
	case OPERATOR_LESS_THAN:
	{
		return checkLessThan(leftProperty, rightProperty);
	}
	case OPERATOR_LESS_THAN_OR_EQUAL:
	{
		return checkLessThanOrEquals(leftProperty, rightProperty);
	}
	case OPERATOR_GREATER_THAN:
	{
		return checkGreaterThan(leftProperty, rightProperty);
	}
	case OPERATOR_GREATER_THAN_OR_EQUAL:
	{
		return checkGreaterThanOrEquals(leftProperty, rightProperty);
	}
	case OPERATOR_PLUS_EQUAL:
	{
		executePlusEqualsOperator(leftProperty, rightProperty);

		return false;
	}
	case OPERATOR_MINUS_EQUAL:
	{
		executeMinusEqualsOperator(leftProperty, rightProperty);

		return false;
	}
	case OPERATOR_MUL_EQUAL:
	{
		executeMulEqualsOperator(leftProperty, rightProperty);

		return false;
	}
	case OPERATOR_DIV_EQUAL:
	{
		executeDivEqualsOperator(leftProperty, rightProperty);

		return false;
	}
	case OPERATOR_POW_EQUAL:
	{
		executePowEqualsOperator(leftProperty, rightProperty);

		return false;
	}
	}

	return false;
}

template <typename T>
bool executeOperator(Array<T> *leftProperty, const std::string &operatorString, TypedProperty<T> *rightProperty, int index = -1, bool reverse = false)
{
	Operator op = OPERATOR_STRING_MAP.find(operatorString)->second;

	switch (op)
	{
	case OPERATOR_ASSIGN:
	{
		executeAssignOperator(leftProperty, rightProperty, index, reverse);

		return false;
	}
	case OPERATOR_PLUS_EQUAL:
	{
		executePlusEqualsOperator(leftProperty, rightProperty, index, reverse);
	
		return false;
	}
	case OPERATOR_MINUS_EQUAL:
	{
		executeMinusEqualsOperator(leftProperty, rightProperty, index, reverse);
	
		return false;
	}
	case OPERATOR_MUL_EQUAL:
	{
		executeMulEqualsOperator(leftProperty, rightProperty, index, reverse);
		
		return false;
	}
	case OPERATOR_DIV_EQUAL:
	{
		executeDivEqualsOperator(leftProperty, rightProperty, index, reverse);
	
		return false;
	}
	case OPERATOR_POW_EQUAL:
	{
		executePowEqualsOperator(leftProperty, rightProperty, index, reverse);
		
		return false;
	}
	}

	return false;
}

void executeAssignOperator(Property *leftProperty, Property *rightProperty)
{
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		*v = *vRight;

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		*v = *vRight;

		return;
	}
	else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(leftProperty))
	{
		TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightProperty);
		*v = *vRight;

		std::string vFormattedString = v->getValue();
		replaceAllSubstrings(vFormattedString, "\\n", NEWLINE_STRING);
		v->setValue(vFormattedString);

		vFormattedString = v->getValue();
		replaceAllSubstrings(vFormattedString, "\\\"", QUOTE_STRING);
		v->setValue(vFormattedString);

		return;
	}
	else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(leftProperty))
	{
		TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(rightProperty);
		*v = *vRight;

		return;
	}
}

void executeArrayCopyOperator(Property *leftProperty, Property *rightProperty)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		Array<int>* vRight = dynamic_cast<Array<int>*>(rightProperty);
		int* value = v->getValue();
		int* newValue = vRight->getValue();

		for (int i = 0; i < v->getSize(); ++i)
			value[i] = newValue[i];

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		Array<double>* vRight = dynamic_cast<Array<double>*>(rightProperty);
		double* value = v->getValue();
		double* newValue = vRight->getValue();

		for (int i = 0; i < v->getSize(); ++i)
			value[i] = newValue[i];

		return;
	}
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(leftProperty))
	{
		Array<std::string>* vRight = dynamic_cast<Array<std::string>*>(rightProperty);
		std::string* value = v->getValue();
		std::string* newValue = vRight->getValue();

		for (int i = 0; i < v->getSize(); ++i)
			value[i] = newValue[i];

		return;
	}
	else if (Array<bool>* v = dynamic_cast<Array<bool>*>(leftProperty))
	{
		Array<bool>* vRight = dynamic_cast<Array<bool>*>(rightProperty);
		bool* value = v->getValue();
		bool* newValue = vRight->getValue();

		for (int i = 0; i < v->getSize(); ++i)
			value[i] = newValue[i];

		return;
	}
}

void executeAssignOperator(Property *leftProperty, Property *rightProperty, int index, bool reverse = false)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		int* value = v->getValue();
		int newValue = vRight->getValue();

		if (reverse == false)
			value[index] = newValue;
		else 
			vRight->setValue(value[index]);

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		double* value = v->getValue();
		double newValue = vRight->getValue();

		if (reverse == false)
			value[index] = newValue;
		else
			vRight->setValue(value[index]);

		return;
	}
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(leftProperty))
	{
		TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightProperty);
		std::string* value = v->getValue();
		std::string tempValue = vRight->getValue();

		if (reverse == false)
		{
			value[index] = tempValue;

			std::string vFormattedString = value[index];
			replaceAllSubstrings(vFormattedString, "\\n", NEWLINE_STRING);
			value[index] = vFormattedString;

			vFormattedString = value[index];
			replaceAllSubstrings(vFormattedString, "\\""", QUOTE_STRING);
			value[index] = vFormattedString;
		}
		else
		{
			vRight->setValue(value[index]);

			std::string vFormattedString = vRight->getValue();
			replaceAllSubstrings(vFormattedString, "\\n", NEWLINE_STRING);
			vRight->setValue(vFormattedString);

			vFormattedString = value[index];
			replaceAllSubstrings(vFormattedString, "\\""", QUOTE_STRING);
			value[index] = vFormattedString;
		}

		return;
	}
	else if (Array<bool>* v = dynamic_cast<Array<bool>*>(leftProperty))
	{
		TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(rightProperty);
		bool* value = v->getValue();
		bool newValue = vRight->getValue();

		if (reverse == false)
			value[index] = newValue;
		else
			vRight->setValue(value[index]);

		return;
	}
}

void executePlusEqualsOperator(Property *leftProperty, Property *rightProperty)
{
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		*v += *vRight;

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		*v += *vRight;

		return;
	}
	else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(leftProperty))
	{
		TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightProperty);
		*v += *vRight;

		std::string vFormattedString = v->getValue();
		replaceAllSubstrings(vFormattedString, "\\n", NEWLINE_STRING);
		v->setValue(vFormattedString);

		vFormattedString = v->getValue();
		replaceAllSubstrings(vFormattedString, "\\""", QUOTE_STRING);
		v->setValue(vFormattedString);

		return;
	}
}

void executePlusEqualsOperator(Property *leftProperty, Property *rightProperty, int &index, bool reverse = false)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		int* value = v->getValue();
		int newValue = vRight->getValue();

		if (reverse == false)
			value[index] += newValue;
		else
			vRight->setValueNoRef(newValue + value[index]);

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		double* value = v->getValue();
		double newValue = vRight->getValue();

		if (reverse == false)
			value[index] += newValue;
		else
			vRight->setValueNoRef(newValue + value[index]);

		return;
	}
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(leftProperty))
	{
		TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(rightProperty);
		std::string* value = v->getValue();
		std::string tempValue = vRight->getValue();

		if (reverse == false)
		{
			value[index] += tempValue;

			std::string vFormattedString = value[index];
			replaceAllSubstrings(vFormattedString, "\\n", NEWLINE_STRING);
			value[index] = vFormattedString;

			vFormattedString = value[index];
			replaceAllSubstrings(vFormattedString, "\\""", QUOTE_STRING);
			value[index] = vFormattedString;
		}
		else
		{
			vRight->setValue(tempValue + value[index]);

			std::string vFormattedString = vRight->getValue();
			replaceAllSubstrings(vFormattedString, "\\n", NEWLINE_STRING);
			vRight->setValue(vFormattedString);

			vFormattedString = value[index];
			replaceAllSubstrings(vFormattedString, "\\""", QUOTE_STRING);
			value[index] = vFormattedString;
		}

		return;
	}
}

void executeMinusEqualsOperator(Property *leftProperty, Property *rightProperty)
{
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		*v -= *vRight;

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		*v -= *vRight;

		return;
	}
}

void executeMinusEqualsOperator(Property *leftProperty, Property *rightProperty, int &index, bool reverse = false)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		int* value = v->getValue();
		int newValue = vRight->getValue();

		if (reverse == false)
			value[index] -= newValue;
		else
			vRight->setValueNoRef(newValue - value[index]);

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		double* value = v->getValue();
		double newValue = vRight->getValue();

		if (reverse == false)
			value[index] -= newValue;
		else
			vRight->setValueNoRef(newValue - value[index]);

		return;
	}
}

void executeMulEqualsOperator(Property *leftProperty, Property *rightProperty)
{
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		*v *= *vRight;

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		*v *= *vRight;

		return;
	}
}

void executeMulEqualsOperator(Property *leftProperty, Property *rightProperty, int &index, bool reverse)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		int* value = v->getValue();
		int newValue = vRight->getValue();

		if (reverse == false)
			value[index] *= newValue;
		else
			vRight->setValueNoRef(newValue * value[index]);

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		double* value = v->getValue();
		double newValue = vRight->getValue();

		if (reverse == false)
			value[index] *= newValue;
		else
			vRight->setValueNoRef(newValue * value[index]);

		return;
	}
}

void executeDivEqualsOperator(Property *leftProperty, Property *rightProperty)
{
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		*v /= *vRight;

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		*v /= *vRight;

		return;
	}
}

void executeDivEqualsOperator(Property *leftProperty, Property *rightProperty, int &index, bool reverse)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		int* value = v->getValue();
		int newValue = vRight->getValue();

		if (reverse == false)
			value[index] /= newValue;
		else
			vRight->setValueNoRef(newValue / value[index]);

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		double* value = v->getValue();
		double newValue = vRight->getValue();

		if (reverse == false)
			value[index] /= newValue;
		else
			vRight->setValueNoRef(newValue / value[index]);

		return;
	}
}

void executePowEqualsOperator(Property *leftProperty, Property *rightProperty)
{
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		*v ^= *vRight;

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		*v ^= *vRight;

		return;
	}
}

void executePowEqualsOperator(Property *leftProperty, Property *rightProperty, int &index, bool reverse)
{
	if (Array<int>* v = dynamic_cast<Array<int>*>(leftProperty))
	{
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(rightProperty);
		int* value = v->getValue();
		int newValue = vRight->getValue();

		if (reverse == false)
			value[index] = pow(value[index], newValue);
		else
			vRight->setValueNoRef(pow(newValue, value[index]));

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(leftProperty))
	{
		TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(rightProperty);
		double* value = v->getValue();
		double newValue = vRight->getValue();

		if (reverse == false)
			value[index] = pow(value[index], newValue);
		else
			vRight->setValueNoRef(pow(newValue, value[index]));

		return;
	}
}

#endif