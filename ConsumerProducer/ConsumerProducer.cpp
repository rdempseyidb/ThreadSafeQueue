// ConsumerProducer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CountedThreadSafeQueue.h"

using namespace std;
using namespace thread_safe_queue;

namespace
{
	CountedThreadSafeQueue<int>* ptsq;

	int rangeRand()
	{
		int u = (int)((double)rand() / (RAND_MAX + 1) * 50);
		u = 25 - u;
		return u;
	}

	int producer()
	{
		int i = 0;
		for (;;)
		{
			ptsq->push(i++);
			Sleep(45 + rangeRand());
		}
		return 0;
	}

	int consumer()
	{
		for (;;)
		{
			int i = ptsq->pop();
			Sleep(50 + rangeRand());
		}
		return 0;
	}

}

int main()
{
	CountedThreadSafeQueue<int> tsq(10);
	assert(tsq.empty());
	assert(tsq.size() == 0);
	tsq.push(1);
	assert(!tsq.empty());
	assert(tsq.size() == 1);
	int x = tsq.front();
	assert(x == 1);
	tsq.pop();

	ptsq = &tsq;
	boost::thread t1(producer);
	boost::thread t2(consumer);

	t2.join();
	t1.join();

    return 0;
}

