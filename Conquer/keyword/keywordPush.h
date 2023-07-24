#ifndef KEYWORD_PUSH_H
#define KEYWORD_PUSH_H

void processPushKeyword(const std::string &statement)
{
	Property *basicProperty = gStore->get(statement);

	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
		gStore->pushToStack(v);
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
		gStore->pushToStack(v);
	else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
		gStore->pushToStack(v);
	else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
		gStore->pushToStack(v);
	else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
		gStore->pushToStack(*&v);
	else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
		gStore->pushToStack(v);
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
		gStore->pushToStack(v);
	else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
		gStore->pushToStack(v);
}

#endif