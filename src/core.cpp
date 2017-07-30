#include "../include/yal/core.h"

#include <iostream>

#include "../include/yal/sinks.h"

artec::yal::Core& artec::yal::instance()
{
    static Core core;
    return core;
}

artec::yal::Core::Core()
    : printers_{ printSeverity, printTime, printText }
    , threshold_(Severity::Info)
{
    sinks_.push_back(std::make_unique<StdStreamSink>(std::cout));

    start();
}

artec::yal::Core::~Core()
{
    if (thread_.joinable())
    {
        stop();
    }
}

void artec::yal::Core::setSinks(SinkList& sinks)
{
    sinks_.swap(sinks);
}

void artec::yal::Core::setPrinters(PrinterList& printers)
{
    printers_.swap(printers);
}

void artec::yal::Core::setThreshold(Severity level)
{
    threshold_ = level;
}

artec::yal::Severity artec::yal::Core::threshold() const
{
    return threshold_;
}

void artec::yal::Core::start()
{
    if (keepWorking_.test_and_set())
    {
        throw std::logic_error("yal already running");
    }

    buffer_.clear();

    keepWorking_.test_and_set();

    std::packaged_task<void ()> task(
        [this]()
        {
            mainLoop();
        });

    future_ = task.get_future();

    thread_ = std::thread(std::move(task));
}

artec::yal::Core::future_t artec::yal::Core::stop()
{
    if (!thread_.joinable())
    {
        throw std::logic_error("yal already stopped");
    }

    keepWorking_.clear();
    bufferNotEmptyCondition_.notify_one();

    thread_.join();
    keepWorking_.clear();

    return std::move(future_);
}

void artec::yal::Core::putEntry(Entry&& entry)
{
    {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        buffer_.push_back(std::move(entry));
    }

    bufferNotEmptyCondition_.notify_one();
}

void artec::yal::Core::mainLoop()
{
    while (keepWorking_.test_and_set())
    {
        EntryList entries;
        {
            std::unique_lock<decltype(mutex_)> lock(mutex_);
            while (buffer_.empty())
            {
                if (!keepWorking_.test_and_set())
                {
                    return;
                }

                bufferNotEmptyCondition_.wait(lock);
            }
            entries.swap(buffer_);
        }

        process(entries);
    }

    std::lock_guard<decltype(mutex_)> lock(mutex_);
    process(buffer_);
}

void artec::yal::Core::process(const EntryList& entries)
{
    for (const auto& entry : entries)
    {
        for (auto& sink : sinks_)
        {
            bool isFirst = true;
            for (auto& printer : printers_)
            {
                if (isFirst)
                {
                    isFirst = false;
                }
                else
                {
                    sink->addSeparator();
                }
                printer(*sink, entry);
            }

            sink->endOfEntry();
        }
    }

    for (auto& sink : sinks_)
    {
        sink->flush();
    }
}
