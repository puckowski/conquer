
#ifndef SCOPE_STACK_H
#define SCOPE_STACK_H

#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <unordered_map>

#include "Array.h"
#include "Property.h"
#include "TypedProperty.h"

class ScopeStack
{
private:
	std::unordered_map<std::string, std::vector<std::string>*> mScopeMap;

	std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, std::vector<std::string>*>>>> mScopeVal;

	void clearScopeMap()
	{
		for (std::pair<const std::string, std::vector<std::string>*> &scopePair : mScopeMap)
		{
			scopePair.second->clear();
			delete scopePair.second;
		}

		mScopeMap.clear();
	}

protected:

public:
	ScopeStack()
	{
	}

	~ScopeStack()
	{
		clearScopeMap();
	}
	/*
	void add(const std::string &functionName, const std::string &varName)
	{
		mScopeVal = mScopeMap.find(functionName);

		if (mScopeVal == mScopeMap.end())
		{
			std::vector<std::string> *scopeList = new std::vector<std::string>();
			mScopeMap.insert({ functionName, scopeList });

			scopeList->push_back(varName);
		}
		else
			mScopeVal->second->push_back(varName);
	}

	void removeScopeList(const std::string &functionName)
	{
		mScopeVal = mScopeMap.find(functionName);

		if (mScopeVal != mScopeMap.end())
		{
			mScopeVal->second->clear();
			delete mScopeVal->second;

			mScopeMap.erase(functionName);
		}
	}
	*/
};

static ScopeStack* gScopeStack;
static std::mutex  gScopeMutex;

inline ScopeStack* acquireScopeStack()
{
	gScopeMutex.lock();

	return gScopeStack;
}

#endif