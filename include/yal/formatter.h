#pragma once

#include <functional>

#include <fmt/format.h>

#include "entries.h"

namespace artec
{
    namespace yal
    {
        class Formatter
        {
        public:
            template <class T1>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry });
                };
            }

            template <class T1, class T2>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry });
                };
            }

            template <class T1, class T2, class T3>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry }, T3{ entry });
                };
            }

            template <class T1, class T2, class T3, class T4>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry }, T3{ entry }, T4{ entry });
                };
            }

            template <class T1, class T2, class T3, class T4, class T5>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry }, T3{ entry }, T4{ entry }, T5{ entry });
                };
            }

            template <class T1, class T2, class T3, class T4, class T5, class T6>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry }, T3{ entry }, T4{ entry }, T5{ entry }, T6{ entry });
                };
            }

            template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry }, T3{ entry }, T4{ entry }, T5{ entry }, T6{ entry }, T7{ entry });
                };
            }

            template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
            void setFormat(const std::string& format)
            {
                formatFunction_ = [format](const Entry& entry)
                {
                    return fmt::format(format, T1{ entry }, T2{ entry }, T3{ entry }, T4{ entry }, T5{ entry }, T6{ entry }, T7{ entry }, T8{ entry });
                };
            }

            std::string format(const Entry& entry)
            {
                return formatFunction_(entry);
            }

        private:
            using FormatFunction = std::function<std::string(const Entry&)>;
            FormatFunction formatFunction_;
        };
    }
}
