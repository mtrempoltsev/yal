#include "../include/yal/sinks.h"

artec::yal::AbstractSink::~AbstractSink() noexcept
{
}

artec::yal::StdStreamSink::StdStreamSink(std::ostream& stream) noexcept
    : stream_(stream)
{
}

void artec::yal::StdStreamSink::writeEntryItem(const std::string& text)
{
    stream_ << text;
}

void artec::yal::StdStreamSink::addSeparator()
{
    stream_ << ' ';
}

void artec::yal::StdStreamSink::endOfEntry()
{
    stream_ << '\n';
}

void artec::yal::StdStreamSink::flush()
{
    stream_.flush();
}

artec::yal::FileSink::FileSink(const std::string& fileName)
    : file_(fileName, std::ios::binary)
{
    if (!file_)
    {
        throw std::runtime_error("can't open log file: '" + fileName + "'");
    }
}

void artec::yal::FileSink::writeEntryItem(const std::string& text)
{
    file_.write(text.data(), text.size());
}

void artec::yal::FileSink::addSeparator()
{
    file_.put(' ');
}

void artec::yal::FileSink::endOfEntry()
{
    file_.put('\n');
}

void artec::yal::FileSink::flush()
{
    file_.flush();
}
