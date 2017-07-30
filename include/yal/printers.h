#pragma once

#include <vector>

namespace artec
{
    namespace yal
    {
        class AbstractSink;
        struct Entry;

        using PrintFunction = void (*)(AbstractSink& sink, const Entry& entry);
        using PrinterList = std::vector<PrintFunction>;

        void printSeverity(AbstractSink& sink, const Entry& entry);
        void printText(AbstractSink& sink, const Entry& entry);
        void printTimezone(AbstractSink& sink, const Entry& entry);
        void printTime(AbstractSink& sink, const Entry& entry);
        void printDate(AbstractSink& sink, const Entry& entry);
        void printThread(AbstractSink& sink, const Entry& entry);
        void printPlaceInCode(AbstractSink& sink, const Entry& entry);
    }
}
