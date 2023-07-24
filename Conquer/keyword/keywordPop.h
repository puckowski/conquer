#ifndef KEYWORD_POP_H
#define KEYWORD_POP_H

#include <algorithm>

void processPopKeyword(const std::string &statement)
{
	Property *basicProperty2 = gStore->get(statement);

	Property *basicProperty = gStore->peekStack();
	
	std::cout << &basicProperty2 << "  " << &basicProperty << std::endl;
	std::swap(*basicProperty2, *basicProperty);
	delete basicProperty;
	std::cout << &basicProperty2 << "  " << &basicProperty << std::endl;

	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
		*basicProperty2 = *v;
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
		*basicProperty2 = *v;
	else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
		*basicProperty2 = *v;
	else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
		*basicProperty2 = *v;
	else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty)) {
		Array<int>* v2 = dynamic_cast<Array<int>*>(basicProperty2);
		std::cout << v << std::endl;
		v2 = *&v;
		//std::cout << &v << "  " << &v2 << std::endl;
		//std::swap(*v2, *v);// *v2 = *v;
		//std::cout << &v << "  " << &v2 << std::endl;
	}
	else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
		*basicProperty2 = *v;
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
		*basicProperty2 = *v;
	else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
		*basicProperty2 = *v;
	/*
	if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
	else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
		executeArrayCopyOperator(v, gStore->peekStack());
		*/

	gStore->popFromStack();
}

#endif