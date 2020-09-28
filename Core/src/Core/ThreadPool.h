#pragma once

#include "Core.h"

#include <functional>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <queue>

namespace Engine
{

	class ENGINE_API ThreadPool
	{
	public:
		using Task = std::function<void()>;
	public:
		ThreadPool(size_t size);
		~ThreadPool();

		void enqueue(Task task);

		template<class T, class... Ts>
		std::future<T> enqueue(std::function<T(Ts...)> task, Ts... args)
		{
			auto wrapper = std::make_shared<std::packaged_task<T()>>(std::move(task));

			enqueue([=] {
				(*wrapper)(args...);
			});

			return wrapper->get_future();
		}

	private:
		std::vector<std::thread> threads;
		std::queue<Task> tasks;

		std::mutex mutex;
		std::condition_variable cv;
		std::atomic<bool> drain = false;
	};

}