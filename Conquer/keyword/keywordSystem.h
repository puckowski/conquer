
#ifndef KEYWORD_SYSTEM_H
#define KEYWORD_SYSTEM_H

void processSystemKeyword(const std::string &statement)
{
	Property *basicProperty = gStore->get(statement);

	if (basicProperty == nullptr)
		system(statement.c_str());
	else
	{
		TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
		system(v->getValue().c_str());
	}
}

#endif