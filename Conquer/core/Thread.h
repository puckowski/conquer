
#ifndef THREAD_H
#define THREAD_H

static int                 gThreadCount;
static tthread::fast_mutex gThreadCountMutex;

inline void incrementThreadCount()
{
	gThreadCountMutex.lock();
	gThreadCount++;
	gThreadCountMutex.unlock();
}

inline void decrementThreadCount()
{
	gThreadCountMutex.lock();
	gThreadCount--;
	gThreadCountMutex.unlock();
}

inline int getThreadCount()
{
	gThreadCountMutex.lock();

	return gThreadCount;
}

#endif