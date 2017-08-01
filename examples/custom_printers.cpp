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

/*
output:

INFO  TID 18528 2017-09-01 +0300 05:04:45.675185 1 C:\work\yal\examples\custom_printers.cpp:17
WARN  TID 18528 2017-09-01 +0300 05:04:45.675281 message: 2 C:\work\yal\examples\custom_printers.cpp:18
ERROR TID 18528 2017-09-01 +0300 05:04:45.675292 3 0x00000000 C:\work\yal\examples\custom_printers.cpp:19
*/