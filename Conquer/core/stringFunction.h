
#ifndef STRING_FUNCTION_H
#define STRING_FUNCTION_H

void processStringToBoolFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(argProperty);
	bool boolString;
	std::istringstream(v->getValue()) >> std::boolalpha >> boolString;
	vRight->setValueNoRef(boolString);
}

void processStringToIntFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(argProperty);
	vRight->setValueNoRef(stoi(v->getValue()));
}

void processStringToDoubleFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(argProperty);
	vRight->setValueNoRef(stod(v->getValue()));
}

void processSubstrFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v1 = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement1 = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty1 = gStore->get(statement1);

	std::string statement2 = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty2 = gStore->get(statement2);

	std::string statement3 = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty3 = gStore->get(statement3);

	bool createdArg1 = false, createdArg2 = false;

	if (argProperty1 == nullptr)
	{
		createdArg1 = true;

		argProperty1 = createNewInt(statement1);
	}

	if (argProperty2 == nullptr)
	{
		createdArg2 = true;

		argProperty2 = createNewInt(statement2);
	}

	TypedProperty<int>* v2 = dynamic_cast<TypedProperty<int>*>(argProperty1);
	TypedProperty<int>* v3 = dynamic_cast<TypedProperty<int>*>(argProperty2);
	TypedProperty <std::string>* v4 = dynamic_cast<TypedProperty<std::string>*>(argProperty3);
	v4->setValue(v1->getValue().substr(v2->getValue(), v3->getValue()));

	if (createdArg1)
		delete argProperty1;

	if (createdArg2)
		delete argProperty2;
}

void processFindFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement1 = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty1 = gStore->get(statement1);

	std::string statement2 = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty2 = gStore->get(statement2);

	bool createdArg1 = false;

	if (argProperty1 == nullptr)
	{
		createdArg1 = true;

		argProperty1 = createNewString(statement1);
	}

	TypedProperty<std::string>* vMiddle = dynamic_cast<TypedProperty<std::string>*>(argProperty1);
	TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(argProperty2);
	vRight->setValueNoRef(v->getValue().find(vMiddle->getValue()));

	if (createdArg1)
		delete argProperty1;
}

void processLengthFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(argProperty);
	vRight->setValueNoRef(v->getValue().length());
}

void processTakeLineFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	TypedProperty<std::string> * vRight = dynamic_cast<TypedProperty<std::string>*>(argProperty);

	std::string vValue = v->getValue();
	int newlineIndex = vValue.find('\n');

	if (newlineIndex != std::string::npos)
	{
		vRight->setValueNoRef(vValue.substr(0, newlineIndex));
		v->setValue(vValue.substr(newlineIndex + 1));
	}
	else
	{
		vRight->setValueNoRef(vValue.substr(0, newlineIndex));
		v->setValueNoRef("");
	}
}

#endif