#include "../include/yal/printers.h"

#include <iomanip>
#include <sstream>
#include <unordered_map>

#include <fmt/ostream.h>

#include "../include/yal/entries.h"
#include "../include/yal/utils.h"

namespace
{
    artec::yal::Stream& appendZeroIfNeeded(artec::yal::Stream& stream, int value)
    {
        if (value < 10)
        {
            stream << '0';
        }
        stream << value;
        return stream;
    }
}

void artec::yal::printSeverity(Stream& stream, const Entry& entry)
{
    stream << toString(entry.level);
}

void artec::yal::printText(Stream& stream, const Entry& entry)
{
    stream << entry.text;
}

void artec::yal::printTimezone(Stream& stream, const Entry& entry)
{
    //TODO need to improve performance (localtime is very expensive)

    const auto time = clock_t::to_time_t(entry.time);
    const auto localtime = std::localtime(&time);

    std::stringstream buf;
    buf << std::put_time(localtime, "%z");
    stream << buf.str();
}

void artec::yal::printTime(Stream& stream, const Entry& entry)
{
    const auto time = clock_t::to_time_t(entry.time);
    const auto upToSecond = clock_t::from_time_t(time);
    const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(entry.time - upToSecond).count();

    const auto utcTime = toDateTime<clock_t>(entry.time);

    appendZeroIfNeeded(stream, utcTime.hour) << ':';
    appendZeroIfNeeded(stream, utcTime.min) << ':';
    appendZeroIfNeeded(stream, utcTime.sec) << '.' << microseconds;
}

void artec::yal::printDate(Stream& stream, const Entry& entry)
{
    const auto utcTime = toDateTime<clock_t>(entry.time);

    stream << utcTime.year << '-';
    appendZeroIfNeeded(stream, utcTime.month + 1) << '-';
    appendZeroIfNeeded(stream, utcTime.day);
}

void artec::yal::printThread(Stream& stream, const Entry& entry)
{
    stream.write("TID {0}", entry.thread);
}

void artec::yal::printPlaceInCode(Stream& stream, const Entry& entry)
{
    stream << entry.file << ':' << entry.line;
}
