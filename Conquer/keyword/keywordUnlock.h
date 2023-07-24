
#ifndef KEYWORD_UNLOCK_H
#define KEYWORD_UNLOCK_H

inline void processUnlockKeyword(const std::string &functionName)
{
	gStore->unlock(functionName);
}

#endif