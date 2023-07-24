
#ifndef KEYWORD_DELETE_H
#define KEYWORD_DELETE_H

void executeDeleteKeyword(const std::string &variableName)
{
	Property *basicProperty = gStore->get(variableName);

	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
	else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
	{
		gStore->remove(v);

		return;
	}
}

#endif

