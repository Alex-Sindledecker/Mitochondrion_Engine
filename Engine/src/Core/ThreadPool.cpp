#include "pch.h"
#include "ThreadPool.h"

namespace Engine
{

	ThreadPool::ThreadPool(size_t size, bool finishTasks)
	{
		this->finishTasks = finishTasks;
		for (int i = 0; i < size; i++)
		{
			threads.emplace_back([=] {
				while (true)
				{
					Task task;
					{
						std::unique_lock<std::mutex> lk(mutex);

						cv.wait(lk, [=] { return drain || !tasks.empty(); });

						if (drain && (tasks.empty() || !finishTasks))
							return;

						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
			});
		}
	}

	ThreadPool::~ThreadPool()
	{
		drain = true;
		cv.notify_all();
		for (std::thread& t : threads)
			t.join();
	}

}