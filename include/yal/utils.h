#pragma once

#include <fmt/format.h>

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

        template <class clock_t>
        DateTime toDateTime(const typename clock_t::time_point& timePoint) noexcept
        {
            const int32_t time = static_cast<int32_t>(clock_t::to_time_t(timePoint));

            const int32_t secondsInDay = 24 * 60 * 60;

            const int32_t daysByMonth[2][12] =
            {
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
                { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
            };

            auto leapYear = [](int32_t year) noexcept { return (!((year) % 4) && (((year) % 100) || !((year) % 400))); };
            auto daysInYear = [&leapYear](int32_t year) noexcept { return (leapYear(year) ? 366 : 365); };

            const int32_t dayclock = time % secondsInDay;

            int32_t year = 1970;

            DateTime result;

            result.sec = dayclock % 60;
            result.min = (dayclock % 3600) / 60;
            result.hour = dayclock / 3600;

            int32_t dayno = time / secondsInDay;
            while (dayno >= daysInYear(year))
            {
                dayno -= daysInYear(year);
                year++;
            }

            result.year = year;
            result.month = 0;
            while (dayno >= daysByMonth[leapYear(year)][result.month])
            {
                dayno -= daysByMonth[leapYear(year)][result.month];
                result.month++;
            }
            result.month++;
            result.day = dayno + 1;

            return result;
        }

        template <int PtrSize>
        inline void printPointer(fmt::MemoryWriter& buffer, const void* value);

        template <>
        inline void printPointer<4>(fmt::MemoryWriter& buffer, const void* value) // x86
        {
            buffer.write("{0:0=#10x}", reinterpret_cast<const uint32_t>(value));
        }

        template <>
        inline void printPointer<8>(fmt::MemoryWriter& buffer, const void* value) // x64
        {
            buffer.write("{0:0=#10x}", reinterpret_cast<const uint64_t>(value));
        }
    }
}
