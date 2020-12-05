#include "mepch.h"
#include "Utilities.h"

namespace util
{

	ThreadPool::ThreadPool(size_t size)
	{
		start(size);
	}

	ThreadPool::~ThreadPool()
	{
		if (!drain)
			finish();
	}

	void ThreadPool::start(size_t size)
	{
		for (int i = 0; i < size; i++)
		{
			threads.emplace_back([=] {
				//Thread loop
				while (true)
				{
					//Get the next task and execute it
					Task task;
					{
						std::unique_lock<std::mutex> lk(mutex);

						cv.wait(lk, [=] { return drain || !tasks.empty(); });

						if (drain && tasks.empty())
							return;

						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
				});
		}
	}

	void ThreadPool::finish()
	{
		drain = true;
		cv.notify_all();
		for (std::thread& t : threads)
			t.join();
	}

	static auto startTime = std::chrono::high_resolution_clock::now();

	double getCurrentTime()
	{
		auto current = std::chrono::high_resolution_clock::now() - startTime;
		return current.count() / 1000000000.0;
	}

	std::string getCurrentTimeString()
	{
		auto current = std::chrono::high_resolution_clock::now() - startTime;

		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(current);
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(current);
		auto milliseconds = (current % 1000000000) / 1000000.0;

		std::stringstream ss;
		ss << minutes.count() << ":" << seconds.count() % 60 << ":" << milliseconds.count();
		return ss.str();
	}

	StackAllocator::StackAllocator(size_t bufferSize)
	{
		buffer = new byte[bufferSize];
	}

	StackAllocator::~StackAllocator()
	{
		delete buffer;
	}

}