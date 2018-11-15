#pragma once

#include <mutex>
#include <condition_variable>
#include <deque>

#define _BLOCK_

template <typename T>
class BlockingQueue {
public:
	using MutexLockGuard = std::lock_guard<std::mutex>;

	BlockingQueue()
		: mutex_(),
		cv_(),
		queue_()
	{
	}

	BlockingQueue(const BlockingQueue &) = delete;
	BlockingQueue& operator=(const BlockingQueue &) = delete;

	void put(const T &x)
	{
		{
			MutexLockGuard lock(mutex_);
			queue_.push_back(x);
		}
		cv_.notify_one();
	}

	void put(T &&x)
	{
		{
			MutexLockGuard lock(mutex_);
			queue_.push_back(std::move(x));
		}
		cv_.notify_one();
	}

	T take()
	{
		std::unique_lock<std::mutex> lock(mutex_);
#ifdef _BLOCK_
		cv_.wait(lock, [this] {  return !this->queue_.empty(); });
#else
		if (queue_.empty())
			return T();
#endif

		T front(std::move(queue_.front()));
		queue_.pop_front();

		return  front;
	}

	size_t size() const
	{
		MutexLockGuard lock(mutex_);
		return queue_.size();
	}

private:
	mutable std::mutex mutex_;
	std::condition_variable cv_;
	std::deque<T> queue_;
};


