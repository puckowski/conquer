
#ifndef INT_FUNCTION_H
#define INT_FUNCTION_H

void processIntToDoubleFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<double>* vRight = dynamic_cast<TypedProperty<double>*>(argProperty);
	vRight->setValueNoRef(static_cast<double>(v->getValue()));
}

void processIntToStringFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(argProperty);
	vRight->setValueNoRef(std::to_string(v->getValue()));
}

void processIntAbsFunction(Property *basicProperty)
{
	TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty);
	v->setValueNoRef(abs(v->getValue()));
}

void processNormalizeIntArrayFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	Array<int>* v = dynamic_cast<Array<int>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty1 = gStore->get(statement);

	bool createdArg1 = false;

	if (argProperty1 == nullptr)
	{
		createdArg1 = true;

		argProperty1 = createNewInt(statement);
	}

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty2 = gStore->get(statement);

	bool createdArg2 = false;

	if (argProperty2 == nullptr)
	{
		createdArg2 = true;

		argProperty2 = createNewInt(statement);
	}

	TypedProperty<int>* numOne = dynamic_cast<TypedProperty<int>*>(argProperty1);
	TypedProperty<int>* numTwo = dynamic_cast<TypedProperty<int>*>(argProperty2);

	int arraySize = v->getSize();
	int* imageData = v->getValue();
	int floor = numOne->getValue();
	int ceiling = numTwo->getValue();

	int minValue = INT_MAX, maxValue = INT_MIN, i;

	for (i = 0; i < arraySize; ++i)
	{
		if (imageData[i] < minValue)
			minValue = imageData[i];
		else if (imageData[i] > maxValue)
			maxValue = imageData[i];
	}

	int a = ceiling - floor / (maxValue - minValue);
	int b = ceiling - a * maxValue;

	for (i = 0; i < arraySize; ++i)
		imageData[i] = a * imageData[i] + b;

	/*
	const int maxMinusMin = maxValue - minValue;
	const int denominator = maxMinusMin + floor;
	const int ceilingMinusFloor = ceiling - floor;

	for (i = 0; i < arraySize; ++i)
		imageData[i] = ((ceilingMinusFloor * (imageData[i] - minValue)) / denominator);

	for (i = 0; i < arraySize; ++i)
		imageData[i] += floor;
	*/

	if (createdArg1)
		delete argProperty1;

	if (createdArg2)
		delete argProperty2;
}

#endif