
#ifndef KEYWORD_PRINT_H
#define KEYWORD_PRINT_H

void executePrintKeyword(std::string &statement)
{
	std::queue<std::string> mPrintQueue;
	std::string nextString;
	int outputIndex, arrayIndex;

	while (statement.find("<<") != std::string::npos)
	{
		outputIndex = statement.find_first_of("<<");

		nextString = statement.substr(0, outputIndex);

		while (nextString.find("\"") != std::string::npos && countSubstring(nextString, "\"") < 2)
		{
			outputIndex = statement.find(OPERATOR_MAP.find(OPERATOR_OUTPUT)->second, outputIndex + 1);
			nextString = statement.substr(0, outputIndex);
		}

		statement = statement.substr(outputIndex + (OPERATOR_MAP.find(OPERATOR_OUTPUT)->second).length(), statement.length());
		mPrintQueue.push(nextString);
	}

	if (statement.empty() == false)
		mPrintQueue.push(statement);

	bool createdTempVar;

	while (mPrintQueue.empty() == false)
	{
		arrayIndex = -1;

		statement = mPrintQueue.front();
		mPrintQueue.pop();

		if (statement == "endl")
		{
			std::cout << std::endl;

			continue;
		}

		if (statement.find("[") != std::string::npos)
			arrayIndex = getArrayIndexAndRemoveBrackets(statement);

		Property *basicProperty = gStore->get(statement);

		if (basicProperty == nullptr)
		{
			Datatype rightHandType = gTypeChecker.getType(statement);

			createdTempVar = true;

			switch (rightHandType)
			{
			case TYPE_INT:
			{
				basicProperty = createNewInt(statement);

				break;
			}
			case TYPE_DOUBLE:
			{
				basicProperty = createNewDouble(statement);

				break;
			}
			case TYPE_STRING:
			{
				basicProperty = createNewString(statement);

				break;
			}
			case TYPE_BOOL:
			{
				basicProperty = createNewBool(statement);

				break;
			}
			}
		}
		else
			createdTempVar = false;

		if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
			std::cout << v;
		else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
			std::cout << v;
		else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
			std::cout << v;
		else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
			std::cout << v;
		else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
			if (arrayIndex >= 0)
				std::cout << v->getValue()[arrayIndex];
			else
				std::cout << v;
		else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
			if (arrayIndex >= 0)
				std::cout << v->getValue()[arrayIndex];
			else
				std::cout << v;
		else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
			if (arrayIndex >= 0)
				std::cout << v->getValue()[arrayIndex];
			else
				std::cout << v;
		else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
			if (arrayIndex >= 0)
				std::cout << v->getValue()[arrayIndex];
			else
				std::cout << v;

		if (createdTempVar == true)
			delete basicProperty;
	}
}

#endif