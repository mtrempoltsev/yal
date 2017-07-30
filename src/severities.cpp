#include "../include/yal/severities.h"

#include <cassert>

const char* artec::yal::toString(Severity severity)
{
    switch (severity)
    {
    case Severity::Debug:   return "DEBUG";
    case Severity::Info:    return "INFO ";
    case Severity::Warning: return "WARN ";
    case Severity::Error:   return "ERROR";
    case Severity::Fatal:   return "FATAL";
    }
    assert(!"invalid severity value");
    return "";
}

std::ostream& artec::yal::operator<<(std::ostream& out, Severity severity)
{
    out << toString(severity);
    return out;
}
