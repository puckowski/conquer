
#ifndef DOUBLE_FUNCTION_H
#define DOBULE_FUNCTION_H

void processDoubleToIntFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(argProperty);
	vRight->setValueNoRef(static_cast<int>(v->getValue()));
}

void processDoubleAbsFunction(Property *basicProperty)
{
	TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty);
	v->setValueNoRef(abs(v->getValue()));
}

void processDoubleToStringFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(argProperty);
	vRight->setValueNoRef(std::to_string(v->getValue()));
}

void processDoubleRandFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty);

	if (mArgumentQueue.empty())
	{
		v->setValueNoRef((double) rand() / (RAND_MAX));

		return;
	}
	else
	{
		std::string statement = mArgumentQueue.front();
		mArgumentQueue.pop();

		Property *argProperty = gStore->get(statement);
		TypedProperty<int>* vRight = dynamic_cast<TypedProperty<int>*>(argProperty);

		bool createdArg = false;

		if (vRight == nullptr)
		{
			createdArg = true;

			vRight = createNewInt(statement);
		}

		const int seed = vRight->getValue();

		if (seed > 0)
			srand(seed);
		else
			srand(time(NULL));

		v->setValueNoRef((double) rand() / (RAND_MAX));

		if (createdArg)
			delete argProperty;
	}
}

#endif