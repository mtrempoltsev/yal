#pragma once

#include <chrono>

namespace artec
{
    namespace yal
    {
        struct DateTime
        {
            int year;
            int month;
            int day;
            int hour;
            int min;
            int sec;
        };

        DateTime toDateTime(const std::chrono::system_clock::time_point& timePoint) noexcept;
    }
}
