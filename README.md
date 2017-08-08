ArtecGroup YAL is fast and very simple logger


## How to build

From this directory:
```
mkdir build
cd build
cmake ..
make
```

## Using the logger

```
#include <yal/yal.h>

int main()
{
    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);
    return 0;
}
```

Console output:

```
INFO  05:06:58.26726 1
WARN  05:06:58.26925 message: 2
ERROR 05:06:58.26943 3 0x00000000
```


## Set custom sinks

```
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
```


## Customazing formatting

```
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
```

Console output:
```
INFO  [TID: 0x000029a4, 2017-09-08, 14:30:45.739321 +0300] : 1                    <C:\work\yal\examples\custom_formatting.cpp:17>
WARN  [TID: 0x000029a4, 2017-09-08, 14:30:45.739380 +0300] : message: 2           <C:\work\yal\examples\custom_formatting.cpp:18>
ERROR [TID: 0x000029a4, 2017-09-08, 14:30:45.739389 +0300] : 3 0x00000000         <C:\work\yal\examples\custom_formatting.cpp:19>
```


## Write a log message only if the condition is true
```
auto result = foo();
YAL_ERROR_IF(result != Status::Success) << "Error: " << result;
```
