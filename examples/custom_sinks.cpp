#include <iostream>

#include <yal/yal.h>

int main()
{
    artec::yal::SinkList sinks;
    sinks.push_back(std::make_unique<artec::yal::StdStreamSink>(std::cerr));
    sinks.push_back(std::make_unique<artec::yal::FileSink>("log.txt"));
    artec::yal::instance().setSinks(sinks);

    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);

    return 0;
}

/*
output (std::cerr and file):

INFO  05:06:58.26726 1
WARN  05:06:58.26925 message: 2
ERROR 05:06:58.26943 3 0x00000000
*/
