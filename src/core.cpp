#include "../include/yal/core.h"

#include <iostream>

artec::yal::Core& artec::yal::instance()
{
    static Core core;
    return core;
}

artec::yal::Core::Core()
    : threshold_(Severity::Info)
{
    formatter_.setFormat<SeverityItem, TimeItem, TextItem>("{0} {1} {2}");
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

artec::yal::Formatter& artec::yal::Core:: getFormatter()
{
    return formatter_;
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
        return;
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
        std::promise<void> promise;
        promise.set_value();
        return promise.get_future();
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
        const auto message = formatter_.format(entry);

        for (auto& sink : sinks_)
        {
            sink->out(message);
        }
    }

    for (auto& sink : sinks_)
    {
        sink->flush();
    }
}
