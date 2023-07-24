
#ifndef KEYWORD_DETACH_H
#define KEYWORD_DETACH_H

void processDetachKeyword(const std::string &functionName)
{
	Property *basicProperty = gStore->get(functionName);
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
	
	incrementThreadCount();
	std::thread newThread(runAsChild, v->getValue(), std::this_thread::get_id(), false, true);
	newThread.detach();
}

#endif
