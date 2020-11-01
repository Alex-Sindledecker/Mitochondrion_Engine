#pragma once

#include "mito/Core/MitochondriaAPI.h"

#include <functional>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <queue>

namespace mito
{

	template<class T>
	static bool futureIsReady(std::future<T>& f)
	{
		return f.valid() && f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
	}

	class MITO_API ThreadPool
	{
	public:
		using Task = std::function<void()>;
	public:
		ThreadPool() {}
		ThreadPool(size_t size);
		~ThreadPool();

		void start(size_t size);
		void finish();

		template<class T, class... Ts>
		auto enqueue(T task, Ts... args) -> std::future<decltype(task(args...))>
		{
			auto wrapper = std::make_shared<std::packaged_task<decltype(task(args...))(Ts...)>>(std::move(task));

			{
				std::lock_guard<std::mutex> lk(mutex);
				tasks.push([=] { (*wrapper)(args...); });
			}
			cv.notify_one();

			return wrapper->get_future();
		}

		inline const unsigned int getTaskCount() { return tasks.size(); }

	private:
		std::vector<std::thread> threads;
		std::queue<Task> tasks;

		std::mutex mutex;
		std::condition_variable cv;
		std::atomic<bool> drain = false;
	};

}