
#ifndef BOOL_FUNCTION_H
#define BOOL_FUNCTION_H

void processBoolToStringFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);
	TypedProperty<std::string>* vRight = dynamic_cast<TypedProperty<std::string>*>(argProperty);
	vRight->setValueNoRef(std::to_string(v->getValue()));
}

#endif