
#ifndef TYPED_PROPERTY_H
#define TYPED_PROPERTY_H

#include "..\datatype\Datatype.h"
#include "..\variable\Property.h"

enum VariableFunction
{
	STRING_LENGTH,
	STRING_FIND,
	STRING_SUBSTR,
	FILE_EXIST,
	FILE_REMOVE,
	FILE_READ_INTO_ARRAY,
	INT_TO_DOUBLE,
	DOUBLE_TO_INT,
	INT_TO_STRING,
	DOUBLE_TO_STRING,
	BOOL_TO_STRING,
	FILE_OPEN,
	FILE_CLOSE,
	FILE_WRITE_ARRAY,
	INT_NORMALIZE_ARRAY,
	INT_ABS,
	DOUBLE_ABS,
	DOUBLE_RAND,
	STRING_TAKE_LINE,
	FILE_FILES_IN_DIR,
	STRING_TO_INT,
	STRING_TO_DOUBLE,
	STRING_TO_BOOL
};

const std::map<std::string, VariableFunction> VARIABLE_FUNCTIONS_STRING_MAP =
{
	{ "2_length",          STRING_LENGTH        },
	{ "2_find",            STRING_FIND          },
	{ "2_substr",          STRING_SUBSTR        },
	{ "4_exist",           FILE_EXIST           },
	{ "4_remove",          FILE_REMOVE          },
	{ "4_read_into_array", FILE_READ_INTO_ARRAY },
	{ "0_to_double",       INT_TO_DOUBLE        },
	{ "1_to_int",          DOUBLE_TO_INT        },
	{ "0_to_string",       INT_TO_STRING        },
	{ "1_to_string",       DOUBLE_TO_STRING     },
	{ "3_to_string",       BOOL_TO_STRING       },
	{ "4_open",            FILE_OPEN            },
	{ "4_close",           FILE_CLOSE           },
	{ "4_write_array",     FILE_WRITE_ARRAY     },
	{ "0_normalize",       INT_NORMALIZE_ARRAY  },
	{ "0_abs",             INT_ABS              },
	{ "1_abs",             DOUBLE_ABS           },
	{ "1_rand",            DOUBLE_RAND          },
	{ "2_take_line",       STRING_TAKE_LINE     },
	{ "4_list_files",      FILE_FILES_IN_DIR    },
	{ "2_to_int",          STRING_TO_INT        },
	{ "2_to_double",       STRING_TO_DOUBLE     },
	{ "2_to_bool",         STRING_TO_BOOL       }
};

template <typename T>
class TypedProperty : public Property
{
private:
	T mValue;	

protected:

public:
	TypedProperty(const std::string &name, const int &type, T value) : Property(name, type), mValue(value)
	{
	}

	inline T getValue()
	{
		return mValue;
	}

	inline void setValueNoRef(T newValue)
	{
		mValue = newValue;
	}

	inline void setValue(T &newValue)
	{
		mValue = newValue;
	}

	inline void addValueNoRef(T newValue)
	{
		mValue += newValue;
	}

	inline void addValue(T &newValue)
	{
		mValue += newValue;
	}

	inline void subtractValueNoRef(T newValue)
	{
		mValue -= newValue;
	}

	inline void subtractValue(T &newValue)
	{
		mValue -= newValue;
	}

	inline void multiplyValueNoRef(T newValue)
	{
		mValue *= newValue;
	}

	inline void multiplyValue(T &newValue)
	{
		mValue *= newValue;
	}

	inline void divideValueNoRef(T newValue)
	{
		mValue /= newValue;
	}

	inline void raiseValue(T &newValue)
	{
		mValue = pow(mValue, newValue);
	}

	inline void raiseValueNoRef(T newValue)
	{
		mValue = pow(mValue, newValue);
	}

	template <typename T>
	inline void operator=(TypedProperty<T> &rhs)
	{
		mValue = rhs.getValue();
	}
};

template <typename T>
std::ostream& operator<<(std::ostream &output, TypedProperty<T> *typedVariable)
{
	std::cout << typedVariable->getValue();

	return output;
}

template <typename T>
inline bool checkEquals(TypedProperty<T> *lhs, TypedProperty<T> *rhs)
{
	return (lhs->getValue() == rhs->getValue());
}

template <typename T>
inline bool checkNotEquals(TypedProperty<T> *lhs, TypedProperty<T> *rhs)
{
	return (lhs->getValue() != rhs->getValue());
}

template <typename T>
inline bool checkLessThan(TypedProperty<T> *lhs, TypedProperty<T> *rhs)
{
	return (lhs->getValue() < rhs->getValue());
}

template <typename T>
inline bool checkLessThanOrEquals(TypedProperty<T> *lhs, TypedProperty<T> *rhs)
{
	return (lhs->getValue() <= rhs->getValue());
}

template <typename T>
inline bool checkGreaterThan(TypedProperty<T> *lhs, TypedProperty<T> *rhs)
{
	return (lhs->getValue() > rhs->getValue());
}

template <typename T>
inline bool checkGreaterThanOrEquals(TypedProperty<T> *lhs, TypedProperty<T> *rhs)
{
	return (lhs->getValue() >= rhs->getValue());
}

template <typename T>
inline TypedProperty<T> operator+=(TypedProperty<T> &lhs, TypedProperty<T> &rhs)
{
	lhs.addValueNoRef(rhs.getValue());

	return lhs;
}

template <typename T>
inline TypedProperty<T> operator-=(TypedProperty<T> &lhs, TypedProperty<T> &rhs)
{
	lhs.subtractValueNoRef(rhs.getValue());

	return lhs;
}

template <typename T>
inline TypedProperty<T> operator*=(TypedProperty<T> &lhs, TypedProperty<T> &rhs)
{
	lhs.multiplyValueNoRef(rhs.getValue());

	return lhs;
}

template <typename T>
inline TypedProperty<T> operator/=(TypedProperty<T> &lhs, TypedProperty<T> &rhs)
{
	lhs.divideValueNoRef(rhs.getValue());

	return lhs;
}

template <typename T>
inline TypedProperty<T> operator^=(TypedProperty<T> &lhs, TypedProperty<T> &rhs)
{
	lhs.raiseValueNoRef(rhs.getValue());

	return lhs;
}

#endif