#include "../include/yal/entries.h"

#include "../include/yal/core.h"

artec::yal::Entry::Entry(Severity severityLevel, const char* const fileName, int lineOfFile) noexcept
    : level(severityLevel)
    , file(fileName)
    , line(lineOfFile)
    , time(ClockType::now())
    , thread(std::this_thread::get_id())
{
}

artec::yal::Entry::Entry(Entry&& moved) noexcept
    : level(moved.level)
    , file(moved.file)
    , line(moved.line)
    , time(moved.time)
    , thread(std::move(moved.thread))
    , text(std::move(moved.text))
{
}

artec::yal::EntryMaker::EntryMaker(Severity severityLevel, const char* const fileName, int lineOfFile)
    : entry_(severityLevel, fileName, lineOfFile)
{
}

artec::yal::EntryMaker::~EntryMaker()
{
    entry_.text = std::move(buffer_.str());
    instance().putEntry(std::move(entry_));
}
