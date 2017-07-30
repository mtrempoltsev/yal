#include "../include/yal/printers.h"

#include <iomanip>
#include <sstream>
#include <unordered_map>

#include "../include/yal/entries.h"
#include "../include/yal/sinks.h"

void artec::yal::printSeverity(AbstractSink& sink, const Entry& entry)
{
    sink.writeEntryItem(toString(entry.level));
}

void artec::yal::printText(AbstractSink& sink, const Entry& entry)
{
    sink.writeEntryItem(entry.text);
}

void artec::yal::printTimezone(AbstractSink& sink, const Entry& entry)
{
    const auto time = clock_t::to_time_t(entry.time);
    const auto localtime = std::localtime(&time);

    std::stringstream buf;
    buf << std::put_time(localtime, "%z");
    sink.writeEntryItem(buf.str());
}

void artec::yal::printTime(AbstractSink& sink, const Entry& entry)
{
    const auto time = clock_t::to_time_t(entry.time);
    const auto upToSecond = clock_t::from_time_t(time);
    const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(entry.time - upToSecond).count();
    const auto localtime = std::localtime(&time);

    std::stringstream buf;
    buf << std::put_time(localtime, "%T") << '.' << microseconds;
    sink.writeEntryItem(buf.str());
}

void artec::yal::printDate(AbstractSink& sink, const Entry& entry)
{
    const auto time = clock_t::to_time_t(entry.time);
    const auto localtime = std::localtime(&time);

    std::stringstream buf;
    buf << std::put_time(localtime, "%F");
    sink.writeEntryItem(buf.str());
}

void artec::yal::printThread(AbstractSink& sink, const Entry& entry)
{
    static std::unordered_map<std::thread::id, std::string> threadToString;

    auto it = threadToString.find(entry.thread);
    if (it == std::end(threadToString))
    {
        std::stringstream buf;
        buf << "tid: " << std::setw(5) <<  entry.thread;
        threadToString.emplace(entry.thread, buf.str());
        sink.writeEntryItem(buf.str());
    }
    else
    {
        sink.writeEntryItem(it->second);
    }
}

void artec::yal::printPlaceInCode(AbstractSink& sink, const Entry& entry)
{
    sink.writeEntryItem(fmt::format("{0}:{1}", entry.file, entry.line));
}
