#include "../include/yal/items.h"

#include <iomanip>
#include <sstream>

#include "../include/yal/entries.h"
#include "../include/yal/utils.h"

namespace
{
    fmt::BasicWriter<char>& appendZeroIfNeeded(fmt::BasicWriter<char>& stream, int value)
    {
        if (value < 10)
        {
            stream << '0';
        }
        stream << value;
        return stream;
    }

    const char* findEnd(const char* begin)
    {
        if (*begin == '}')
        {
            return begin + 1;
        }

        const char* end = begin + 1;
        while (*end && *end != '}')
            ++end;
        return end + 1;
    }

    std::string getFormat(const char* begin, const char* end)
    {
        std::string format = "{";
        format.append(begin, end);
        return format;
    }
}

#define YAL_FORMAT_VALUE(value) \
    const char* end = findEnd(begin); \
    if (begin + 1 != end) \
    { \
        formatter.writer().write(getFormat(begin, end), (value)); \
    } \
    else \
    { \
        formatter.writer() << (value); \
    } \
    begin = end;

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::SeverityItem& item)
{
    using namespace artec::yal;

    YAL_FORMAT_VALUE(toString(item.entry.level))
}

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::TextItem& item)
{
    using namespace artec::yal;

    YAL_FORMAT_VALUE(item.entry.text)
}

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::TimezoneItem& item)
{
    //TODO need to improve performance (localtime is very expensive)

    using namespace artec::yal;

    const auto time = ClockType::to_time_t(item.entry.time);
    const auto localtime = std::localtime(&time);

    std::stringstream buf;
    buf << std::put_time(localtime, "%z");
    formatter.writer() << buf.str();

    begin = findEnd(begin);
}

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::TimeItem& item)
{
    using namespace artec::yal;

    const auto time = ClockType::to_time_t(item.entry.time);
    const auto upToSecond = ClockType::from_time_t(time);
    const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(item.entry.time - upToSecond).count();

    const auto utcTime = toDateTime(item.entry.time);

    appendZeroIfNeeded(formatter.writer(), utcTime.hour) << ':';
    appendZeroIfNeeded(formatter.writer(), utcTime.min) << ':';
    appendZeroIfNeeded(formatter.writer(), utcTime.sec) << '.' << microseconds;

    begin = findEnd(begin);
}

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::DateItem& item)
{
    using namespace artec::yal;

    const auto utcTime = toDateTime(item.entry.time);

    formatter.writer() << utcTime.year << '-';
    appendZeroIfNeeded(formatter.writer(), utcTime.month + 1) << '-';
    appendZeroIfNeeded(formatter.writer(), utcTime.day);

    begin = findEnd(begin);
}

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::ThreadItem& item)
{
    using namespace artec::yal;

    std::stringstream buf;
    buf << item.entry.thread;
    const auto tid = std::stoul(buf.str());

    YAL_FORMAT_VALUE(tid)
}

void fmt::format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::PlaceInCodeItem& item)
{
    using namespace artec::yal;

    formatter.writer() << item.entry.file << ':' << item.entry.line;

    begin = findEnd(begin);
}

#undef YAL_FORMAT_VALUE
