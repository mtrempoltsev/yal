#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <thread>

#include <fmt/format.h>

#include <yal/severities.h>
#include <yal/utils.h>

namespace artec
{
    namespace yal
    {
        using ClockType = std::chrono::system_clock;

        class Core;

        struct Entry final
        {
            Entry(Severity severityLevel, const char* const fileName, size_t lineOfFile) noexcept;

            Entry(const Entry&) = delete;
            Entry& operator=(const Entry&) = delete;

            Entry(Entry&& moved) noexcept;
            Entry& operator=(Entry&&) = delete;

            Severity level;
            const char* file;
            int line;
            ClockType::time_point time;
            std::thread::id thread;
            std::string text;
        };

        using EntryList = std::vector<Entry>;

        class EntryMaker final
        {
        public:
            EntryMaker(Severity severityLevel, const char* const fileName, size_t lineOfFile);
            ~EntryMaker();

            EntryMaker(const EntryMaker&) = delete;
            EntryMaker& operator=(const EntryMaker&) = delete;

            EntryMaker(EntryMaker&&) = delete;
            EntryMaker& operator=(EntryMaker&&) = delete;

            template <class T>
            EntryMaker& operator<<(const T& value)
            {
                buffer_ << value;
                return *this;
            }

            template <class T>
            EntryMaker& operator<<(T* value)
            {
                printPointer(buffer_, value);
                return *this;
            }

            EntryMaker& operator<<(const char* value)
            {
                buffer_ << value;
                return *this;
            }

        private:
            template <class T>
            typename std::enable_if<sizeof(T*) == 4, void>::type printPointer(fmt::MemoryWriter& buffer, const T* value)
            {
                buffer.write("{0:0=#10x}", reinterpret_cast<const uint32_t>(value));
            }

            template <class T>
            typename std::enable_if<sizeof(T*) == 8, EntryMaker&>::type printPointer(fmt::MemoryWriter& buffer, const T* value)
            {
                buffer.write("{0:0=#10x}", reinterpret_cast<const uint64_t>(value));
            }

        private:
            Entry entry_;
            fmt::MemoryWriter buffer_;
        };
    }
}
