
#ifndef GLOBAL_H
#define GLOBAL_H

#include "..\file\FileStore.h"
#include "variable\VariableStore.h"

static std::thread::id gMainThreadId;

inline void setup()
{
	gMainThreadId = std::this_thread::get_id();

	gStore     = new VariableStore();
	gFileStore = new FileStore();

	gStore->addRootThreadLevel();
}

inline void cleanup()
{
	delete gFileStore;
	delete gStore;
}

#endif