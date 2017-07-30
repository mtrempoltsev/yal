#pragma once

#include <ostream>

namespace artec
{
    namespace yal
    {
        enum class Severity
        {
            Debug,
            Info,
            Warning,
            Error,
            Fatal
        };

        const char* toString(Severity severity);
        std::ostream& operator<<(std::ostream& out, Severity severity);
    }
}
