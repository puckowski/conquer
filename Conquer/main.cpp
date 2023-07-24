
#ifndef MAIN_CPP
#define MAIN_CPP

#define cimg_OS 2
#define cimg_display 0
#define cimg_verbosity 0

#include <mutex>
#include <queue>
#include <iostream>

#include "core\file.h"
#include "core\global.h"
#include "core\header.h"
#include "core\Thread.h"

#include "core\timer.h"

#include "variable\variable.h"

#include "keyword\Keyword.h"
#include "keyword\keywordPop.h"
#include "keyword\keywordCall.h"
#include "keyword\keywordRead.h"
#include "keyword\keywordJoin.h"
#include "keyword\keywordLock.h"
#include "keyword\keywordPush.h"
#include "keyword\keywordPrint.h"
#include "keyword\keywordUnlock.h"
#include "keyword\keywordDelete.h"
#include "keyword\keywordDetach.h"
#include "keyword\keywordSystem.h"
#include "keyword\keywordPrintln.h"

std::string getNextCodeBlock(const std::string &code, int &terminatingIndex)
{
	std::string codeBlock;
	terminatingIndex = code.find_first_of("}");

	// Get a substring... from the start of the code to the next close brace, including the close brace itself
	terminatingIndex++;
	codeBlock = code.substr(0, terminatingIndex);

	while (countSubstringExcludingQuotes(codeBlock, "{") > countSubstringExcludingQuotes(codeBlock, "}"))
	{
		// Point index to the next closing brace...
		terminatingIndex = code.find("}", terminatingIndex);

		// Get a substring... from the start of the code to the next close brace, including the close brace itself
		terminatingIndex++;
		codeBlock = code.substr(0, terminatingIndex);
	}

	return codeBlock;
}

inline std::string getNextStatement(const std::string &code, int &terminatingIndex)
{
	terminatingIndex = code.find_first_of(";");
	terminatingIndex++;

	const int codeLength = code.length();

	std::string statement = code.substr(0, terminatingIndex);
	bool terminatingIndexModified = false;

	if (statement.find("\"") != std::string::npos)
	{
		if (codeLength > terminatingIndex)
		{
			int temporaryTerminatingIndex = terminatingIndex;

			while (code.at(temporaryTerminatingIndex) == '"')
			{
				temporaryTerminatingIndex = code.find_first_of(";", temporaryTerminatingIndex + 1);

				if (temporaryTerminatingIndex != std::string::npos) {
					terminatingIndex = temporaryTerminatingIndex;

					terminatingIndexModified = true;
				}
				else
					break;
			}
			
			if (terminatingIndexModified == true)
				terminatingIndex++;
		}
	}

	if(terminatingIndexModified == true)
		statement = code.substr(0, terminatingIndex);
	
	if (statement.find("\"") != std::string::npos)
	{
		if (gStore->endsWithVariableName(code.substr(0, terminatingIndex - 1)))
			return code.substr(0, terminatingIndex - 1);
		else if (stringEndsWith(statement, "endl;"))
			return code.substr(0, terminatingIndex - 1);

		if (codeLength > 3)
		{
			while (code.at(terminatingIndex - 2) != '"' || code.at(terminatingIndex - 3) == '\\') {
				terminatingIndex = code.find(";", terminatingIndex + 1);
				terminatingIndex++;
			}
		}
	}

	return code.substr(0, terminatingIndex - 1);
}

void processNextCodeBlock(const std::string &code, std::string &codeBlock, int &terminatingIndex)
{
	// Get next code block
	codeBlock = getNextCodeBlock(code, terminatingIndex);

	if (startsWithString(codeBlock, KEYWORD_MAP))
	{
		std::string keyword;
		codeBlock = removeStringFromMap(codeBlock, KEYWORD_MAP, keyword);

		Keyword key = KEYWORD_STRING_MAP.find(keyword)->second;

		switch (key)
		{
		case KEYWORD_IF:
		{
			int curlyBraceIndex = codeBlock.find_first_of("{");

			// Should have an open brace... get the evaluation string which starts at the beginning up until the curly brace
			std::string evaluationString = codeBlock.substr(0, curlyBraceIndex);

			// Remove the name from the code block... exclude the opening curly brace here
			codeBlock = codeBlock.substr(curlyBraceIndex + 1, codeBlock.length());

			// At this point... code block should end with a closing curly brace... remove it here
			codeBlock = codeBlock.substr(0, codeBlock.length() - 1);

			if (processVariableStatement(evaluationString))
				run(codeBlock);

			return;
		}
		case KEYWORD_WHILE:
		{
			int curlyBraceIndex = codeBlock.find_first_of("{");

			// Should have an open brace... get the evaluation string which starts at the beginning up until the curly brace
			std::string evaluationString = codeBlock.substr(0, curlyBraceIndex);

			// Remove the name from the code block... exclude the opening curly brace here
			codeBlock = codeBlock.substr(curlyBraceIndex + 1, codeBlock.length());

			// At this point... code block should end with a closing curly brace... remove it here
			codeBlock = codeBlock.substr(0, codeBlock.length() - 1);

			std::string evaluationStringCopy = evaluationString, codeBlockCopy = codeBlock;

			while (processVariableStatement(evaluationStringCopy))
			{
				run(codeBlockCopy);
				
				evaluationStringCopy = evaluationString;
				codeBlockCopy = codeBlock;
			}

			return;
		}
		}
	}
	else
	{
		int curlyBraceIndex = codeBlock.find_first_of("{");

		// Should have an open brace... get the name which starts at the beginning up until the curly brace
		std::string functionName = codeBlock.substr(0, curlyBraceIndex);

		// Remove the name from the code block... exclude the opening curly brace here
		codeBlock = codeBlock.substr(curlyBraceIndex + 1, codeBlock.length());

		// At this point... code block should end with a closing curly brace... remove it here
		codeBlock = codeBlock.substr(0, codeBlock.length() - 1);

		TypedProperty<std::string>* typedProperty = new TypedProperty<std::string>(functionName, 5, codeBlock);
		gStore->add(typedProperty);
	}
}

inline bool codeStartsWithVariableName(const std::string &code)
{
	return gStore->startsWithVariableName(code);
}

bool variableStatementHasHigherPrecedence(const std::string &code, const std::string &statement)
{
	std::string codeCopy = code;
	std::string statementCopy = statement;

	if (startsWithString(statement, DATATYPE_MAP) && codeStartsWithVariableName(code))
	{
		std::string datatype;
		removeStringFromMap(statementCopy, DATATYPE_MAP, datatype);

		std::string variableName;
		gStore->removeVariableName(codeCopy, variableName);

		if (variableName.length() > datatype.length())
			return true;
	}
	
	return false;
}

void processNextStatement(const std::string &code, std::string &statement, int &terminatingIndex)
{
	// Get next statement substring
	statement = getNextStatement(code, terminatingIndex);

	if (startsWithString(statement, DATATYPE_MAP) && variableStatementHasHigherPrecedence(code, statement) == false)
	{
		std::string datatype;
		statement = removeStringFromMap(statement, DATATYPE_MAP, datatype);

		// If we can find an open and close square bracket, we will add a new array
		if (statement.find("[") != std::string::npos)// && statement.find("]") != std::string::npos)
		{
			// Extract the name... from the start of the string up to but not including the open square bracket
			std::string variableName = statement.substr(0, statement.find_first_of("["));

			// Get a substring... from the open square bracket (but not including it) to the end...
			statement = statement.substr(statement.find_first_of("[") + 1, statement.length());
			// And up to the closing square bracket (but not including it)
			statement = statement.substr(0, statement.find_first_of("]"));

			int arraySize = -1;

			try
			{
				arraySize = std::stoi(statement);
			}
			catch (std::exception e)
			{
				//arraySize = -1;
			}

			if (statement.empty() == true && arraySize < 0)
			{
				arraySize = 0;

				addArray(variableName, datatype, arraySize);

				return;
			}
			else if (arraySize < 0)
			{
				Property *basicProperty = gStore->get(statement);
				TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);
				arraySize = v->getValue();
			}

			addArray(variableName, datatype, arraySize);

			return;
		}
		else
		{
			// Normal variable to add
			addTypedProperty(statement, datatype);

			return;
		}
	}
	else if (startsWithString(statement, KEYWORD_MAP))
	{
		std::string keyword;
		statement = removeStringFromMap(statement, KEYWORD_MAP, keyword, MAXIMUM_KEYWORD_LENGTH);

		Keyword key = KEYWORD_STRING_MAP.find(keyword)->second;

		switch (key)
		{
		case KEYWORD_CALL:
		{
			processCallKeyword(statement);

			return; 
		}
		case KEYWORD_IMPORT:
		{
			run(statement, true);

			return; 
		}
		case KEYWORD_PRINT:
		{
			executePrintKeyword(statement);

			return; 
		}
		case KEYWORD_PRINTLN:
		{
			executePrintlnKeyword(statement);

			return; 
		}
		case KEYWORD_DETACH:
		{
			processDetachKeyword(statement);

			return; 
		}
		case KEYWORD_JOIN:
		{
			processJoinKeyword(statement);

			return;
		}
		case KEYWORD_READLN:
		{
			executeReadKeyword(statement);

			return; 
		}
		case KEYWORD_DELETE:
		{
			executeDeleteKeyword(statement);

			return;
		}
		case KEYWORD_SYSTEM:
		{
			processSystemKeyword(statement);

			return;
		}
		case KEYWORD_LOCK:
		{
			processLockKeyword(statement);

			return;
		}
		case KEYWORD_UNLOCK:
		{
			processUnlockKeyword(statement);

			return;
		}
		case KEYWORD_PUSH:
		{
			processPushKeyword(statement);

			return;
		}
		case KEYWORD_POP:
		{
			processPopKeyword(statement);

			return;
		}
		}
	}
	else
	{
		processVariableStatement(statement);

		return;
	}
}

void formatCode(std::string &code)
{
	// Remove all newline characters
	removeAllCharExcludingQuotes(code, '\n');
	removeAllCharExcludingQuotes(code, '\r');
	removeAllCharExcludingQuotes(code, '\t');

	// Remove all whitespace
	removeAllCharExcludingQuotes(code, ' ');
}

void runAsChild(std::string &code, std::thread::id parentId, bool readFromFile, bool decrementThreadCountWhenDone)
{
	gStore->addThreadToThreadLevel(parentId, std::this_thread::get_id());
	
	if (readFromFile)
	{
		if (stringStartsWith(code, "\"")) code = code.substr(1, code.length());
		if (stringEndsWith(code, "\"")) code = code.substr(0, code.length() - 1);

		code = readFile(code);
		formatCode(code);
	}

	std::string statement, codeBlock, stringToOpenBrace;
	int terminatingIndex, semicolonIndex, openBraceIndex, indexOfClose;

	// While we have some code...
	while (code.empty() == false)
	{
		if (code.substr(0, 2) == "/*")
		{
			code = code.substr(2, code.length());
			indexOfClose = code.find("*/");
			code = code.substr(indexOfClose + 2, code.length());

			continue;
		}

		semicolonIndex = code.find_first_of(";");
		openBraceIndex = code.find_first_of("{");

		stringToOpenBrace = code.substr(0, openBraceIndex);

		if (semicolonIndex < openBraceIndex || countSubstring(stringToOpenBrace, "\"") > 0 || openBraceIndex == std::string::npos)
		{
			while (countSubstringExcludingQuotes(code.substr(0, semicolonIndex), ";") < 1) 
				semicolonIndex = code.find(";", semicolonIndex + 1);

			statement = "";
			processNextStatement(code, statement, terminatingIndex);

			// Update the code to reflect what has been parsed by this pass
			code = code.substr(terminatingIndex);

			continue;
		}
		else
		{
			codeBlock = "";
			processNextCodeBlock(code, codeBlock, terminatingIndex);

			// Update the code to reflect what has been parsed by this pass
			code = code.substr(terminatingIndex);

			continue;
		}
	}

	if (decrementThreadCountWhenDone == true && std::this_thread::get_id() != gMainThreadId)
		decrementThreadCount();

	gStore->removeThreadFromThreadLevel(std::this_thread::get_id());
}

void run(std::string &code, bool readFromFile, bool decrementThreadCountWhenDone)
{
	if (readFromFile)
	{
		if (stringStartsWith(code, "\"")) code = code.substr(1, code.length());
		if (stringEndsWith(code, "\"")) code = code.substr(0, code.length() - 1);

		code = readFile(code);
		formatCode(code);
	}

	std::string statement, codeBlock, stringToOpenBrace;
	int terminatingIndex, semicolonIndex, openBraceIndex, indexOfClose;

	// While we have some code...
	while (code.empty() == false)
	{
		if (code.substr(0, 2) == "/*")
		{
			code = code.substr(2, code.length());
			indexOfClose = code.find("*/");
			code = code.substr(indexOfClose + 2, code.length());

			continue;
		}

		semicolonIndex = code.find_first_of(";");
		openBraceIndex = code.find_first_of("{");

		stringToOpenBrace = code.substr(0, openBraceIndex);

		if (semicolonIndex < openBraceIndex && semicolonIndex != std::string::npos || countSubstring(stringToOpenBrace, "\"") > 0 || openBraceIndex == std::string::npos)
		{
			while (countSubstringExcludingQuotes(code.substr(0, semicolonIndex), ";") < 1) 
				semicolonIndex = code.find(";", semicolonIndex + 1);

			statement = "";
			processNextStatement(code, statement, terminatingIndex);

			// Update the code to reflect what has been parsed by this pass
			code = code.substr(terminatingIndex);

			continue;
		}
		else
		{
			codeBlock = "";
			processNextCodeBlock(code, codeBlock, terminatingIndex);

			// Update the code to reflect what has been parsed by this pass
			code = code.substr(terminatingIndex);

			continue;
		}
	}

	if (decrementThreadCountWhenDone == true && std::this_thread::get_id() != gMainThreadId)
		decrementThreadCount();
}

void main(int argc, char *argv[])
{
	//srand(time(NULL));

	if (argc == 2 && std::string(argv[1]) == "-i") {
		printSoftwareInformation();

		return;
	}

	setup();
	std::string code;
	
	if (argc == 2) {
		code = readFile(std::string(argv[1]));
	
		auto t1 = getTime();
		formatCode(code);
		run(code);
		auto t2 = getTime();
		printTimeDifferenceAll(t1, t2);
	}
	else {
		std::cout << "cqr> ";
		std::getline(std::cin, code);

		while (code != "exit") {
			auto t1 = getTime();
			formatCode(code);
			run(code);
			auto t2 = getTime();
			printTimeDifferenceAll(t1, t2);

			std::cout << "cqr> ";
			std::getline(std::cin, code);
		}
	}

	cleanup();
}

#endif