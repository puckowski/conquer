
#ifndef KEYWORD_TRUE_H
#define KEYWORD_TRUE_H

inline TypedProperty<bool>* createNewBoolFromString(const std::string &value)
{
	if (value == "true")
		return new TypedProperty<bool>("", 3, true);
	else
		return new TypedProperty<bool>("", 3, false);

	return nullptr;
}

#endif
