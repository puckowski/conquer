
#ifndef KEYWORD_JOIN_H
#define KEYWORD_JOIN_H

void processJoinKeyword(const std::string &functionName)
{
	Property *basicProperty = gStore->get(functionName);
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);
	
	const int startThreadCount = getThreadCount();
	gThreadCountMutex.unlock();

	incrementThreadCount();
	std::thread newThread(runAsChild, v->getValue(), std::this_thread::get_id(), false, true);
	newThread.join();

	while (startThreadCount != getThreadCount()) 
	{
		gThreadCountMutex.unlock();
		std::this_thread::yield();		
	}
				
	gThreadCountMutex.unlock();
}

#endif