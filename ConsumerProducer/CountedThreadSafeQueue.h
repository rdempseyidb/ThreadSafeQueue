#pragma once
#include "ThreadSafeQueue.h"

namespace thread_safe_queue
{

	template <class T>
	class CountedThreadSafeQueue :
		public ThreadSafeQueue<T>
	{
	public:
		explicit CountedThreadSafeQueue(unsigned max);
		~CountedThreadSafeQueue();

		void push(const value_type& val);
		value_type pop();

	private:
		typedef typename ThreadSafeQueue<T> Base;

		unsigned m_max;

		boost::mutex m_implLock;
		boost::condition_variable m_implCond;

	};

	template <class T>
	void CountedThreadSafeQueue<T>::push(const value_type& val)
	{
		boost::mutex::scoped_lock lk(m_implLock);
		if (Base::size() >= m_max)
		{
			do {
				m_implCond.wait(lk);
			} while (Base::size() >= m_max);
		}
		Base::push(val);
		m_implCond.notify_one();
	}

	template <class T>
	typename CountedThreadSafeQueue<T>::value_type CountedThreadSafeQueue<T>::pop()
	{
		boost::mutex::scoped_lock lk(m_implLock);
		if (Base::empty())
		{
			do {
				m_implCond.wait(lk);
			} while (Base::empty());
		}
		value_type val = Base::front();
		Base::pop();
		m_implCond.notify_one();
		return val;
	}

	template <class T>
	CountedThreadSafeQueue<T>::CountedThreadSafeQueue(unsigned max) : m_max(max)
	{
	}


	template <class T>
	CountedThreadSafeQueue<T>::~CountedThreadSafeQueue()
	{
	}

}