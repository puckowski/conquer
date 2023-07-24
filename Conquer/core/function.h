
#ifndef FUNCTION_H
#define FUNCTION_H

#include "intFunction.h"
#include "boolFunction.h"
#include "fileFunction.h"
#include "stringFunction.h"
#include "doubleFunction.h"

const std::string FUNCTION_DATATYPE_PREFIX_STRINGS[5] = { "0_", "1_", "2_", "3_", "4_" };

void processFunctionCallOnVariable(Property *basicProperty, std::string &statement)
{
	statement = statement.substr(1, statement.length() - 2); 
	std::string functionName = statement.substr(0, statement.find_first_of("("));
	statement = statement.substr(statement.find_first_of("(") + 1);

	std::queue<std::string> argumentQueue;

	if (countSubstring(statement, "\"") >= 2)
	{
		int quoteIndex;
		int secondQuoteIndex;
		std::string strToOpenQuote;
		std::string quotedString;

		do
		{
			quoteIndex = statement.find_first_of("\"");

			strToOpenQuote = statement.substr(0, quoteIndex);
			if (stringEndsWith(strToOpenQuote, ",")) strToOpenQuote = strToOpenQuote.substr(0, strToOpenQuote.length() - 1);

			argumentQueue.push(strToOpenQuote);

			statement = statement.substr(quoteIndex, statement.length());
			
			secondQuoteIndex = statement.find("\"", quoteIndex + 1);
			quotedString = statement.substr(0, secondQuoteIndex + 1);

			while (countSubstringExcludingQuotes(quotedString, ",") < 1)
			{
				secondQuoteIndex = statement.find(",", secondQuoteIndex + 1);
				quotedString = statement.substr(0, secondQuoteIndex + 1);
			}
		
			if (stringStartsWith(quotedString, ",")) quotedString = quotedString.substr(1, quotedString.length());

			argumentQueue.push(quotedString);

			statement = statement.substr(secondQuoteIndex + 1, statement.length());
		} 
		while (countSubstring(statement, "\"") >= 2);

		if (stringStartsWith(statement, ",")) statement = statement.substr(1, statement.length());
		if (stringEndsWith(statement, ",")) statement = statement.substr(0, statement.length() - 1);

		argumentQueue.push(statement);
	}
	else
	{
		std::string nextString;
		int commaIndex;

		while (statement.find(",") != std::string::npos)
		{
			commaIndex = statement.find_first_of(",");

			nextString = statement.substr(0, commaIndex);
			statement = statement.substr(commaIndex + 1, statement.length());

			argumentQueue.push(nextString);
		}

		if(statement.empty() == false)
			argumentQueue.push(statement);
	}

	VariableFunction varFunction = VARIABLE_FUNCTIONS_STRING_MAP.find(FUNCTION_DATATYPE_PREFIX_STRINGS[basicProperty->getType()] + functionName)->second;

	switch(varFunction)
	{
	case DOUBLE_TO_INT:
	{
		processDoubleToIntFunction(basicProperty, argumentQueue);

		return;
	}
	case INT_TO_DOUBLE:
	{
		processIntToDoubleFunction(basicProperty, argumentQueue);

		return;
	}
	case INT_TO_STRING:
	{
		processIntToStringFunction(basicProperty, argumentQueue);

		return;
	}
	case DOUBLE_TO_STRING:
	{
		processDoubleToStringFunction(basicProperty, argumentQueue);

		return;
	}
	case BOOL_TO_STRING:
	{
		processBoolToStringFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_READ_INTO_ARRAY:
	{
		processReadIntoArrayFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_LENGTH:
	{
		processLengthFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_FIND:
	{
		processFindFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_SUBSTR:
	{
		processSubstrFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_EXIST:
	{
		processFileExistFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_REMOVE:
	{
		processFileRemoveFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_OPEN:
	{
		processFileOpenFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_CLOSE:
	{
		processFileCloseFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_WRITE_ARRAY:
	{
		processWriteArrayToFileFunction(basicProperty, argumentQueue);

		return;
	}
	case INT_NORMALIZE_ARRAY:
	{
		processNormalizeIntArrayFunction(basicProperty, argumentQueue);

		return;
	}
	case INT_ABS:
	{
		processIntAbsFunction(basicProperty);

		return;
	}
	case DOUBLE_ABS:
	{
		processDoubleAbsFunction(basicProperty);

		return;
	}
	case DOUBLE_RAND:
	{
		processDoubleRandFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_TAKE_LINE:
	{
		processTakeLineFunction(basicProperty, argumentQueue);

		return;
	}
	case FILE_FILES_IN_DIR:
	{
		processGetFilesInDirFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_TO_INT:
	{
		processStringToIntFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_TO_DOUBLE:
	{
		processStringToDoubleFunction(basicProperty, argumentQueue);

		return;
	}
	case STRING_TO_BOOL:
	{
		processStringToBoolFunction(basicProperty, argumentQueue);

		return;
	}
	}
}

#endif