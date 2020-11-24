#pragma once

#include <functional>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <queue>

namespace util
{

	struct Image
	{
		int width, height, channels;
		unsigned char* pixels;
	};

	static void formatString(std::stringstream& ss, const std::string& string, int offset)
	{
		if (ss.str().length() == 0)
			ss << string;
		else
		{
			ss << string.substr(offset);
		}
	}

	template<class T, class... Ts>
	static void formatString(std::stringstream& ss, const std::string& string, int offset, T arg, Ts... args)
	{
		size_t bracketPos = string.find('{', offset);
		if (bracketPos != std::string::npos)
		{
			ss << string.substr(offset, bracketPos - offset);
			if (string[bracketPos + 1] == '}')
			{
				ss << arg;
				formatString(ss, string, bracketPos + 2, args...);
			}
			else
			{
				ss << '{';
				formatString(ss, string, bracketPos + 1, arg, args...);
			}
		}
		else
			ss << string.substr(offset);
	}

	template<class... Ts>
	static std::string formatString(const std::string& string, Ts... args)
	{
		std::stringstream ss;
		formatString(ss, string, 0, args...);
		return ss.str();
	}

	//Checks if a futures value is ready to be aquired
	template<class T>
	static bool futureIsReady(std::future<T>& f)
	{
		return f.valid() && f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
	}

	class ThreadPool
	{
	public:
		using Task = std::function<void()>;
	public:
		ThreadPool() {}
		ThreadPool(size_t size);
		~ThreadPool();

		//Begin thread execution
		void start(size_t size);
		//Finish thread execution
		void finish();

		//Add a task to be executed asynchronously
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

		//Gets the number of tasks currently on the queue
		inline const unsigned int getTaskCount() { return tasks.size(); }

	private:
		std::vector<std::thread> threads;
		std::queue<Task> tasks;

		std::mutex mutex;
		std::condition_variable cv;
		std::atomic<bool> drain = false;
	};

	//Gets the time since the program started
	double getCurrentTime();
	//Stores the current time in dest as MIN:SEC:MIL
	std::string getCurrentTimeString();

	Image loadImage(const char* src);
	void freeImage(Image* image);
	void readFile(const std::string& src, std::string* dest);

}