#pragma once

#include <vector>

#include <fmt/format.h>

namespace artec
{
    namespace yal
    {
        struct Entry;

        using Stream = fmt::MemoryWriter;

        using PrintFunction = void (*)(Stream& stream, const Entry& entry);
        using PrinterList = std::vector<PrintFunction>;

        void printSeverity(Stream& stream, const Entry& entry);
        void printText(Stream& stream, const Entry& entry);
        void printTimezone(Stream& stream, const Entry& entry);
        void printTime(Stream& stream, const Entry& entry);
        void printDate(Stream& stream, const Entry& entry);
        void printThread(Stream& stream, const Entry& entry);
        void printPlaceInCode(Stream& stream, const Entry& entry);
    }
}
