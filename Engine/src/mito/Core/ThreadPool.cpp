#include "mepch.h"
#include "ThreadPool.h"

namespace mito
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
				while (true)
				{
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

}