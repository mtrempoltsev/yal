#include <yal/yal.h>

int main()
{
    artec::yal::instance().getFormatter().setFormat
        <
            artec::yal::SeverityItem,
            artec::yal::ThreadItem,
            artec::yal::DateItem,
            artec::yal::TimeItem,
            artec::yal::TimezoneItem,
            artec::yal::TextItem,
            artec::yal::PlaceInCodeItem
        >
        ("{0} [TID: {1:=#010x}, {2}, {3} {4}] : {5:<20} <{6}>");

    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);

    return 0;
}

/*
output:

INFO  [TID: 0x000029a4, 2017-09-08, 14:30:45.739321 +0300] : 1                    <C:\work\yal\examples\custom_formatting.cpp:17>
WARN  [TID: 0x000029a4, 2017-09-08, 14:30:45.739380 +0300] : message: 2           <C:\work\yal\examples\custom_formatting.cpp:18>
ERROR [TID: 0x000029a4, 2017-09-08, 14:30:45.739389 +0300] : 3 0x00000000         <C:\work\yal\examples\custom_formatting.cpp:19>
*/
