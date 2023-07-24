
#ifndef KEYWORD_CALL_H
#define KEYWORD_CALL_H

void processCallKeyword(const std::string &functionName)
{
	Property *basicProperty = gStore->get(functionName);
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
	run(v->getValue());
}

#endif