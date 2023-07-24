
#ifndef KEYWORD_LOCK_H
#define KEYWORD_LOCK_H

inline void processLockKeyword(const std::string &functionName)
{
	gStore->lock(functionName);
}

#endif