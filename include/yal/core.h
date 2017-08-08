#pragma once

#include <atomic>
#include <future>
#include <mutex>
#include <thread>

#include <yal/entries.h>
#include <yal/items.h>
#include <yal/formatter.h>
#include <yal/sinks.h>

namespace artec
{
    namespace yal
    {
        class Core final
        {
        public:
            Core();
            ~Core();

            void setSinks(SinkList& sinks);

            Formatter& getFormatter();

            void start();

            using future_t = std::future<void>;
            future_t stop();

            void putEntry(Entry&& entry);

            void setThreshold(Severity level);
            Severity threshold() const;

        private:
            void mainLoop();
            void process(const EntryList& entries);

        private:
            std::thread thread_;
            std::mutex mutex_;
            std::condition_variable bufferNotEmptyCondition_;
            future_t future_;
            std::atomic_flag keepWorking_;

            EntryList buffer_;

            SinkList sinks_;

            Formatter formatter_;

            Severity threshold_;
        };

        artec::yal::Core& instance();
    }
}
