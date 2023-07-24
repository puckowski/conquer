
#ifndef KEYWORD_READ_H
#define KEYWORD_READ_H

#include "..\operator\Operator.h"

void executeWriteFile(TypedProperty<std::string> *fileProperty, std::string &statement)
{
	std::queue<std::string> mReadQueue;
	std::string nextString;
	int outputIndex;

	while (statement.find("<<") != std::string::npos)
	{
		outputIndex = statement.find_first_of("<<");

		nextString = statement.substr(0, outputIndex);
		statement = statement.substr(outputIndex + 2, statement.length());

		mReadQueue.push(nextString);
	}

	if (statement.empty() == false)
		mReadQueue.push(statement);

	const std::string filename = fileProperty->getValue();

	FileStore* fileStore = acquireFileStore();
	std::ofstream* myFile = fileStore->get(filename);
	gFileStoreMutex.unlock();

	bool createdNewString;

	while (mReadQueue.empty() == false)
	{
		statement = mReadQueue.front();
		mReadQueue.pop();

		if (statement == "endl")
		{
			*myFile << std::endl;
		
			continue;
		}

		Property *basicProperty = gStore->get(statement);

		if (basicProperty == nullptr)
		{
			createdNewString = true;

			basicProperty = createNewString(statement);
		}
		else
			createdNewString = false;

		if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
			*myFile << v->getValue();
		else if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
			*myFile << v->getValue();
		else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
			*myFile << v->getValue();
		else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
			*myFile << v->getValue();
		
		if (createdNewString)
			delete basicProperty;
	}
}

void executeReadFile(TypedProperty<std::string> *fileProperty, std::string &statement)
{
	std::queue<std::string> mReadQueue;
	std::string nextString;
	int outputIndex;

	while (statement.find(">>") != std::string::npos)
	{
		outputIndex = statement.find_first_of(">>");

		if (outputIndex == std::string::npos)
			continue;

		nextString = statement.substr(0, outputIndex);
		statement = statement.substr(outputIndex + 2, statement.length());

		if (nextString.empty() == true)
			continue;

		mReadQueue.push(nextString);
	}

	if (statement.empty() == false)
		mReadQueue.push(statement);

	while (mReadQueue.empty() == false)
	{
		statement = mReadQueue.front();
		mReadQueue.pop();

		Property *basicProperty = gStore->get(statement);
		TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
		v->setValue(readFile(fileProperty->getValue()));
	}
}

void executeReadKeyword(std::string &statement)
{
	std::queue<std::string> mReadQueue;
	std::string nextString;
	int outputIndex;

	while (statement.find(">>") != std::string::npos)
	{
		outputIndex = statement.find_first_of(">>");

		nextString = statement.substr(0, outputIndex);
		statement = statement.substr(outputIndex + 2, statement.length());

		mReadQueue.push(nextString);
	}

	if (statement.empty() == false)
		mReadQueue.push(statement);

	while (mReadQueue.empty() == false)
	{
		statement = mReadQueue.front();
		mReadQueue.pop();

		Property *basicProperty = gStore->get(statement);

		if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
		{
			std::string value = "";
			std::getline(std::cin, value);

			TypedProperty<int> *tempProperty = createNewIntFromConsole(value);

			executeAssignOperator(v, tempProperty);
			delete tempProperty;
		}
		else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
		{
			std::string value = "";
			std::getline(std::cin, value);

			TypedProperty<double> *tempProperty = createNewDoubleFromConsole(value);

			executeAssignOperator(v, tempProperty);
			delete tempProperty;
		}
		else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
		{
			std::string value = "";
			std::getline(std::cin, value);

			TypedProperty<std::string> *tempProperty = createNewStringFromConsole(value);

			executeAssignOperator(v, tempProperty);
			delete tempProperty;
		}
		else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
		{
			std::string value = "";
			std::getline(std::cin, value);

			TypedProperty<bool> *tempProperty = createNewBoolFromConsole(value);

			executeAssignOperator(v, tempProperty);
			delete tempProperty;
		}
	}
}

#endif