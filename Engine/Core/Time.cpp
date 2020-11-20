#include "mepch.h"
#include "Time.h"

#include <chrono>
#include <sstream>

namespace Time
{

    static auto startTime = std::chrono::high_resolution_clock::now();

    double getElapsedTime()
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

}