#include <yal/yal.h>

int main()
{
    YAL_INFO << 1;
    YAL_WARNING << fmt::format("{0}: {1}", "message", 2);
    YAL_ERROR << 3 << ' ' << static_cast<int*>(nullptr);

    return 0;
}

/*
output:

INFO  05:06:58.26726 1
WARN  05:06:58.26925 message: 2
ERROR 05:06:58.26943 3 0x00000000
*/
