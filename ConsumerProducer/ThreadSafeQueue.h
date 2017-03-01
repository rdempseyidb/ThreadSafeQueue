#pragma once

namespace thread_safe_queue
{

	template <class T>
	class ThreadSafeQueue
	{
	public:
		typedef typename std::deque<T>::size_type size_type;
		typedef typename std::deque<T>::value_type value_type;

		ThreadSafeQueue();
		~ThreadSafeQueue();

		bool empty() const;
		size_type size() const;
		value_type& front();
		const value_type& front() const;
		void push(const value_type& val);
		void pop();

	private:
		mutable boost::mutex m_implLock;
		std::deque<T> m_impl;
	};

	template <class T>
	void ThreadSafeQueue<T>::push(const value_type& val)
	{
		boost::mutex::scoped_lock lk(m_implLock);
		m_impl.push_back(val);
	}

	template <class T>
	void ThreadSafeQueue<T>::pop()
	{
		boost::mutex::scoped_lock lk(m_implLock);
		m_impl.pop_front();
	}

	template <class T>
	const typename ThreadSafeQueue<T>::value_type& ThreadSafeQueue<T>::front() const
	{
		boost::mutex::scoped_lock lk(m_implLock);
		return m_impl.front();
	}

	template <class T>
	typename ThreadSafeQueue<T>::value_type& ThreadSafeQueue<T>::front()
	{
		boost::mutex::scoped_lock lk(m_implLock);
		return m_impl.front();
	}

	template <class T>
	typename ThreadSafeQueue<T>::size_type ThreadSafeQueue<T>::size() const
	{
		boost::mutex::scoped_lock lk(m_implLock);
		return m_impl.size();
	}

	template <class T>
	ThreadSafeQueue<T>::ThreadSafeQueue()
	{
	}

	template <class T>
	ThreadSafeQueue<T>::~ThreadSafeQueue()
	{
	}

	template <class T>
	bool ThreadSafeQueue<T>::empty() const
	{
		boost::mutex::scoped_lock lk(m_implLock);
		return m_impl.empty();
	}

}
