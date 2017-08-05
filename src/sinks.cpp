#include "../include/yal/sinks.h"

artec::yal::StdStreamSink::StdStreamSink(std::ostream& stream) noexcept
    : stream_(stream)
{
}

void artec::yal::StdStreamSink::out(const std::string& text)
{
    stream_ << text << '\n';
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

void artec::yal::FileSink::out(const std::string& text)
{
    file_.write(text.data(), text.size());
    file_.put('\n');
}

void artec::yal::FileSink::flush()
{
    file_.flush();
}
