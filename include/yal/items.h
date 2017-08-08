#pragma once

#include <fmt/format.h>

namespace artec
{
    namespace yal
    {
        struct Entry;

        template <class T>
        struct Item
        {
            const Entry& entry;
        };

        struct SeverityType     {};
        struct TextType         {};
        struct TimezoneType     {};
        struct TimeType         {};
        struct DateType         {};
        struct ThreadType       {};
        struct PlaceInCodeType  {};

        using SeverityItem      = Item<SeverityType>;
        using TextItem          = Item<TextType>;
        using TimezoneItem      = Item<TimezoneType>;
        using TimeItem          = Item<TimeType>;
        using DateItem          = Item<DateType>;
        using ThreadItem        = Item<ThreadType>;
        using PlaceInCodeItem   = Item<PlaceInCodeType>;
    }
}

namespace fmt
{
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::SeverityItem& item);
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::TextItem& item);
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::TimezoneItem& item);
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::TimeItem& item);
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::DateItem& item);
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::ThreadItem& item);
    void format_arg(fmt::BasicFormatter<char>& formatter, const char*& begin, const artec::yal::PlaceInCodeItem& item);
}
