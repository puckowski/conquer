
#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
class Array : public Property
{
private:
	T   *mValue;
	int mNumberOfElements;

protected:

public:
	Array(const std::string &name, const int &type, T &value, const int &numberOfElements) : Property(name, type), mNumberOfElements(numberOfElements)
	{
		mValue = new T[numberOfElements];

		for (int i = 0; i < numberOfElements; ++i)
			mValue[i] = value;
	}

	~Array()
	{
		clean();
	}

	inline void clean()
	{
		if (mValue != nullptr)
			delete[] mValue;
	}

	inline void setValue(T* value, const int &numberOfElements)
	{
		if (mValue != nullptr)
			delete[] mValue;

		mValue = value;
		mNumberOfElements = numberOfElements;
	}

	inline T* getValue()
	{
		return mValue;
	}

	inline int getSize()
	{
		return mNumberOfElements;
	}

	template <typename T>
	inline void operator=(Array<T> &rhs)
	{
		return;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream &output, Array<T> *myArray)
{
	const T* arrayPtr = myArray->getValue();
	const int arraySize = myArray->getSize();

	for (int i = 0; i < arraySize; ++i)
		std::cout << "[" << i << "]: " << arrayPtr[i] << " ";

	return output;
}

#endif