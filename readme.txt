ArtecGroup YAL is fast and very simple logger


How to build
------------

From this directory:
mkdir build
cd build
cmake ..
make


Using the logger
----------------

#include <yal/yal.h>

int main()
{
    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);
    return 0;
}

Console output:

INFO  05:06:58.26726 1
WARN  05:06:58.26925 message: 2
ERROR 05:06:58.26943 3 0x00000000


Set custom sinks
----------------

#include <iostream>

#include <yal/yal.h>

int main()
{
    artec::yal::SinkList sinks;
    sinks.push_back(std::make_unique<artec::yal::StdStreamSink>(std::cerr));
    sinks.push_back(std::make_unique<artec::yal::FileSink>("log.txt"));
#ifdef YAL_USES_BOOST
    sinks.push_back(std::make_unique<artec::yal::RollingFileSink>(".", "rolling_file_"));
#endif
    artec::yal::instance().setSinks(sinks);

    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);

    return 0;
}


Customazing formatting
----------------------

#include <yal/yal.h>

int main()
{
    artec::yal::PrinterList printers
    {
        artec::yal::printSeverity,
        artec::yal::printThread,
        artec::yal::printDate,
        artec::yal::printTimezone,
        artec::yal::printTime,
        artec::yal::printText,
        artec::yal::printPlaceInCode
    };
    artec::yal::instance().setPrinters(printers);

    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);

    return 0;
}

Console output:
INFO  TID 18528 2017-09-01 +0300 05:04:45.675185 1 C:\work\yal\examples\custom_printers.cpp:17
WARN  TID 18528 2017-09-01 +0300 05:04:45.675281 message: 2 C:\work\yal\examples\custom_printers.cpp:18
ERROR TID 18528 2017-09-01 +0300 05:04:45.675292 3 0x00000000 C:\work\yal\examples\custom_printers.cpp:19


Write a log message only if the condition is true
-------------------------------------------------
auto result = foo();
YAL_ERROR_IF(result != Status::Success) << "Error: " << result;
