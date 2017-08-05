#pragma once

#include <string>

namespace artec
{
    namespace yal
    {
        class AbstractSink
        {
        public:
            virtual ~AbstractSink() noexcept {}

            virtual void out(const std::string& text) = 0;
            virtual void flush() = 0;
        };
    }
}
