
#ifndef VARIABLE_STORE_H
#define VARIABLE_STORE_H

#include <stack>

#include "Array.h"
#include "Property.h"
#include "TypedProperty.h"
#include "..\core\strings.h"

class VariableStore;

static VariableStore*      gStore;
static tthread::fast_mutex gStoreMutex;

class VariableStore
{
private:
	std::unordered_map<std::string, Property*>            mVariables;
	std::unordered_map<std::thread::id, std::string>      mThreadIdMap;
	std::unordered_map<std::thread::id, int>              mThreadLevelMap;
	std::unordered_map<std::string, tthread::fast_mutex*> mVariableMutexMap; 
	std::stack<Property*>                                 mVariableStack;

	void cleanArrays()
	{
		Property* basicProperty;

		for (const auto &element : mVariables)
		{
			basicProperty = element.second;

			if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
				v->clean();
			else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
				v->clean();
			else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
				v->clean();
			else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
				v->clean();
		}
	}

	std::string getNameWithThreadId(const std::string &variableName)
	{
		std::thread::id mThreadId = std::this_thread::get_id();
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::thread::id, std::string>>>> mThreadSearchVal = mThreadIdMap.find(mThreadId);

		if (mThreadSearchVal != mThreadIdMap.end())
			return variableName + mThreadSearchVal->second;
		else
		{
			std::ostringstream mStringStream;
			mStringStream << std::this_thread::get_id();

			mThreadIdMap.insert({ mThreadId, mStringStream.str() });

			return variableName + mStringStream.str();
		}
	}

	std::string getNameWithThreadId(const std::string &variableName, const std::thread::id threadId)
	{
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::thread::id, std::string>>>> mThreadSearchVal = mThreadIdMap.find(threadId);
		std::ostringstream mStringStream;

		if (mThreadSearchVal != mThreadIdMap.end())
			return variableName + mThreadSearchVal->second;
		else
		{
			mStringStream << threadId;

			mThreadIdMap.insert({ threadId, mStringStream.str() });

			return variableName + mStringStream.str();
		}
	}

	inline int getThreadLevel(std::thread::id threadId)
	{
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::thread::id, int>>>> mThreadLevelVal = mThreadLevelMap.find(threadId);

		if (mThreadLevelVal != mThreadLevelMap.end())
			return mThreadLevelVal->second;
		else
			return -1;
	}

protected:

public:
	VariableStore()
	{
	}

	~VariableStore()
	{
		clear();
	}

	inline void clear()
	{
		cleanArrays();
		cleanLocks();
		mVariables.clear();
		mThreadLevelMap.clear();
	}

	inline void addRootThreadLevel()
	{
		mThreadLevelMap.insert({ std::this_thread::get_id(), 1 });
	}

	void addThreadToThreadLevel(std::thread::id parentThreadId, std::thread::id newThreadId)
	{
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::thread::id, int>>>> mThreadLevelVal = mThreadLevelMap.find(parentThreadId);

		if (mThreadLevelVal != mThreadLevelMap.end()) 
			mThreadLevelMap.insert({ newThreadId, mThreadLevelVal->second + 1 });
		else 
			return;
	}

	inline void removeThreadFromThreadLevel(std::thread::id threadId)
	{
		mThreadLevelMap.erase(threadId);
	}

	inline void cleanLocks()
	{
		for (std::pair<const std::string, tthread::fast_mutex*> &mutexPair : mVariableMutexMap)
			delete mutexPair.second;

		mVariableMutexMap.clear();
	}

	bool lock(const std::string &varName)
	{
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, tthread::fast_mutex*>>>> mVariableMutexVal = mVariableMutexMap.find(varName);
		tthread::fast_mutex *varMutex = nullptr;

		if (mVariableMutexVal == mVariableMutexMap.end())
		{
			varMutex = new tthread::fast_mutex;
			mVariableMutexMap.insert({ varName, varMutex });
		}
		else
			varMutex = mVariableMutexVal->second;

		varMutex->lock();

		return true;
	}

	void unlock(const std::string &varName)
	{
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, tthread::fast_mutex*>>>> mVariableMutexVal = mVariableMutexMap.find(varName);

		if (mVariableMutexVal == mVariableMutexMap.end()) 
			return;
		else
		{
			tthread::fast_mutex *varMutex = mVariableMutexVal->second;
			varMutex->unlock();
		}
	}
	
	inline void add(Property* var)
	{
		mVariables.insert({ getNameWithThreadId(var->getName()), var });
	}

	template <typename T>
	inline void pushToStack(TypedProperty<T>* typedVar)
	{
		mVariableStack.push(typedVar);
	}

	template <typename T>
	inline void pushToStack(Array<T>* arrayVar)
	{
		mVariableStack.push(arrayVar);
	}

	template <typename T>
	inline void add(TypedProperty<T>* typedVar)
	{
		mVariables.insert({ getNameWithThreadId(typedVar->getName()), typedVar });
	}

	template <typename T>
	inline void add(Array<T>* arrayVar)
	{
		mVariables.insert({ getNameWithThreadId(arrayVar->getName()), arrayVar });
	}

	inline void popFromStack()
	{
		mVariableStack.pop();
	}

	inline Property* peekStack()
	{
		Property* basicProperty = mVariableStack.top();

		if (TypedProperty<int>* v = dynamic_cast<TypedProperty<int>*>(basicProperty))
			return v;
		else if (TypedProperty<double>* v = dynamic_cast<TypedProperty<double>*>(basicProperty))
			return v;
		else if (TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty))
			return v;
		else if (TypedProperty<bool>* v = dynamic_cast<TypedProperty<bool>*>(basicProperty))
			return v;
		else if (Array<int>* v = dynamic_cast<Array<int>*>(basicProperty))
			return v;
		else if (Array<double>* v = dynamic_cast<Array<double>*>(basicProperty))
			return v;
		else if (Array<std::string>* v = dynamic_cast<Array<std::string>*>(basicProperty))
			return v;
		else if (Array<bool>* v = dynamic_cast<Array<bool>*>(basicProperty))
			return v;

		return nullptr;
	}

	template <typename T>
	void remove(TypedProperty<T>* typedVar)
	{
		int mOriginalStoreSize = mVariables.size();
		mVariables.erase(getNameWithThreadId(typedVar->getName()));

		if (mOriginalStoreSize == mVariables.size())
		{
			std::thread::id mThreadId = std::this_thread::get_id();
			int mThreadLevel = getThreadLevel(mThreadId);

			for (std::pair<const std::thread::id, int> threadLevelPair : mThreadLevelMap)
				if (mThreadLevel >= 2 && threadLevelPair.second < mThreadLevel) {
					mVariables.erase(getNameWithThreadId(typedVar->getName(), threadLevelPair.first));
					delete typedVar;

					return;
				}
		}
		else
			delete typedVar;
	}

	template <typename T>
	void remove(Array<T>* arrayVar)
	{
		int mOriginalStoreSize = mVariables.size();
		mVariables.erase(getNameWithThreadId(arrayVar->getName()));

		if (mOriginalStoreSize == mVariables.size())
		{
			std::thread::id mThreadId = std::this_thread::get_id();
			int mThreadLevel = getThreadLevel(mThreadId);

			for (std::pair<const std::thread::id, int> threadLevelPair : mThreadLevelMap)
				if (mThreadLevel >= 2 && threadLevelPair.second < mThreadLevel) {
					mVariables.erase(getNameWithThreadId(arrayVar->getName(), threadLevelPair.first));
					delete arrayVar;

					return;
				}
		}
		else
			delete arrayVar;
	}

	Property* get(const std::string &varName)
	{
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, Property*>>>> mSearchVal = mVariables.find(getNameWithThreadId(varName));

		if (mSearchVal != mVariables.end()) 
			return mSearchVal->second;
		else
		{
			std::thread::id mThreadId = std::this_thread::get_id();
			int mThreadLevel = getThreadLevel(mThreadId);

			for (std::pair<const std::thread::id, int> threadLevelPair : mThreadLevelMap)
				if (mThreadLevel >= 2 && threadLevelPair.second < mThreadLevel)
				{
					mSearchVal = mVariables.find(getNameWithThreadId(varName, threadLevelPair.first));

					if (mSearchVal != mVariables.end()) 
						return mSearchVal->second;
				}
		}

		return nullptr;
	}

	bool startsWithVariableName(const std::string &code)
	{
		gStoreMutex.lock();

		for (const auto &elem : mVariables)
			if (stringStartsWith(code, elem.second->getName())) {
				gStoreMutex.unlock();
				return true;
			}

		gStoreMutex.unlock();

		return false;
	}

	bool endsWithVariableName(const std::string &code)
	{
		gStoreMutex.lock();

		for (const auto &elem : mVariables)
			if (stringEndsWith(code, elem.second->getName())) {
				gStoreMutex.unlock();
				return true;
			}

		gStoreMutex.unlock();

		return false;
	}

	std::string removeVariableName(std::string &code, std::string &variableName)
	{
		std::string mElemName;
		int mElemLength;

		gStoreMutex.lock();

		for (const auto &elem : mVariables)
		{
			mElemName = elem.second->getName();
			mElemLength = mElemName.length();

			if (stringStartsWith(code, mElemName))
				if (mElemLength > variableName.length())
					variableName = mElemName;
		}

		gStoreMutex.unlock();

		replaceSubstring(code, variableName, "");

		return code;
	}
};

#endif