#ifndef PROPERTY_H
#define PROPERTY_H

class Property
{
private:

protected:
	std::string mName;
	int mType;

	void setType(const int &type)
	{
		mType = type;
	}

public:
	Property(const std::string &name) : mName(name)
	{
	}

	Property(const std::string &name, const int &type) : mName(name), mType(type)
	{
	}

	virtual ~Property()
	{
	}

	std::string getName()
	{
		return mName;
	}

	int getType()
	{
		return mType;
	}
};

std::ostream& operator<<(std::ostream &output, Property *variable)
{
	std::cout << "undefined";

	return output;
}

inline bool typesMatch(Property *leftProperty, Property *rightProperty)
{
	return (leftProperty->getType() == rightProperty->getType());
}

inline bool typesMatch(Property &leftProperty, Property &rightProperty)
{
	return (leftProperty.getType() == rightProperty.getType());
}

#endif