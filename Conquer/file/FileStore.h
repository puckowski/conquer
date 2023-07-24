
#ifndef FILE_STORE_H
#define FILE_STORE_H

#include <unordered_map>

#include "core\fast_mutex.h"

class FileStore
{
private:
	std::unordered_map<std::string, std::ofstream*> mFiles;
	std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, std::ofstream*>>>> mSearchVal;

	void cleanFiles()
	{
		for (const auto &element : mFiles)
		{
			element.second->close();
			delete element.second;
		}
	}

protected:

public:
	FileStore()
	{
	}

	~FileStore()
	{
		clear();
	}

	inline void clear()
	{
		cleanFiles();
		mFiles.clear();
	}

	inline void add(const std::string &filename)
	{
		std::ofstream* myFile = new std::ofstream();
		mFiles.insert({ filename, myFile });
	}

	inline bool contains(const std::string &filename)
	{
		return (mFiles.find(filename) != mFiles.end());
	}

	inline std::ofstream* get(const std::string &filename)
	{
		mSearchVal = mFiles.find(filename);

		if (mSearchVal != mFiles.end())
			return mSearchVal->second;
		else
			return nullptr;
	}

	inline void open(const std::string &filename)
	{
		mSearchVal = mFiles.find(filename);

		if (mSearchVal != mFiles.end())
			mSearchVal->second->open(filename, std::ios::out);
	}

	inline void close(const std::string &filename)
	{
		mSearchVal = mFiles.find(filename);

		if (mSearchVal != mFiles.end())
			mSearchVal->second->close();
	}

	inline void remove(const std::string &filename)
	{
		mFiles.erase(filename);
	}
};

static FileStore* gFileStore;
static tthread::fast_mutex gFileStoreMutex;

inline FileStore* acquireFileStore()
{
	gFileStoreMutex.lock();

	return gFileStore;
}

#endif