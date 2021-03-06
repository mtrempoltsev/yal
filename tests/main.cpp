﻿#include <cassert>
#include <iostream>
#include <random>
#include <sstream>

#include <gtest/gtest.h>

#include <yal/utils.h>
#include <yal/yal.h>

TEST(yal, checkToDateTime)
{
    using namespace artec::yal;

    std::default_random_engine generator;
    std::uniform_int_distribution<time_t> distribution(0, std::numeric_limits<int32_t>::max());

    const int N = 100000;
    for (int i = 0; i < N; ++i)
    {
        const auto t = distribution(generator);

        const auto t1 = toDateTime(ClockType::from_time_t(t));
        const auto t2 = std::gmtime(&t);

        EXPECT_EQ(t1.year, t2->tm_year + 1900);
        EXPECT_EQ(t1.month, t2->tm_mon + 1);
        EXPECT_EQ(t1.day, t2->tm_mday);
        EXPECT_EQ(t1.hour, t2->tm_hour);
        EXPECT_EQ(t1.min, t2->tm_min);
        EXPECT_EQ(t1.sec, t2->tm_sec);
    }
}

TEST(yal, checkEntry)
{
    using namespace artec::yal;

    const auto level = Severity::Warning;
    const std::string file = "some_file";
    const auto line = 100;
    const std::string text = "some message";

    Entry x(level, file.c_str(), line);
    x.text = text;

    const auto time = x.time;
    const auto thread = x.thread;

    const auto y = std::move(x);

    EXPECT_EQ(level, y.level);
    EXPECT_EQ(file, y.file);
    EXPECT_EQ(line, y.line);
    EXPECT_EQ(text, y.text);
    EXPECT_EQ(time, y.time);
    EXPECT_EQ(thread, y.thread);
}

TEST(yal, checkPrintPointers)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<TextItem>("{0}");

    artec::yal::instance().start();

    const char* text = "Some Text";
    int* x = 0;
    int* y = (int*) 100;

    YAL_INFO << text;
    YAL_INFO << x;
    YAL_INFO << y;

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "Some Text\n0x00000000\n0x00000064\n");
}

TEST(yal, checkSeverity)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<SeverityItem>("{0}");

    instance().setThreshold(Severity::Debug);

    artec::yal::instance().start();

    YAL_DEBUG << "debug";
    YAL_INFO << "info";
    YAL_WARNING << "warning";
    YAL_ERROR << "error";
    YAL_FATAL << "fatal";

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "DEBUG\nINFO \nWARN \nERROR\nFATAL\n");
}

TEST(yal, checkIfCondition)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<SeverityItem>("{0}");

    instance().setThreshold(Severity::Debug);

    artec::yal::instance().start();

    YAL_DEBUG_IF(1 + 1) << "debug";
    YAL_INFO_IF(1 + 1) << "info";
    YAL_WARNING_IF(1 + 1) << "warning";
    YAL_ERROR_IF(1 + 1) << "error";
    YAL_FATAL_IF(1 + 1) << "fatal";

    YAL_DEBUG_IF(1 + 1) << "debug";
    YAL_INFO_IF(1 - 1) << "info";
    YAL_WARNING_IF(1 + 1) << "warning";
    YAL_ERROR_IF(1 - 1) << "error";
    YAL_FATAL_IF(1 + 1) << "fatal";

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "DEBUG\nINFO \nWARN \nERROR\nFATAL\nDEBUG\nWARN \nFATAL\n");
}

TEST(yal, checkIfConditionThreshold)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<SeverityItem>("{0}");

    instance().setThreshold(Severity::Warning);

    buf.clear();

    artec::yal::instance().start();

    YAL_DEBUG_IF(1 + 1) << "debug";
    YAL_INFO_IF(1 + 1) << "info";
    YAL_WARNING_IF(1 + 1) << "warning";
    YAL_ERROR_IF(1 + 1) << "error";
    YAL_FATAL_IF(1 + 1) << "fatal";

    YAL_DEBUG_IF(1 + 1) << "debug";
    YAL_INFO_IF(1 - 1) << "info";
    YAL_WARNING_IF(1 + 1) << "warning";
    YAL_ERROR_IF(1 - 1) << "error";
    YAL_FATAL_IF(1 + 1) << "fatal";

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "WARN \nERROR\nFATAL\nWARN \nFATAL\n");
}

TEST(yal, checkThreshold)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<SeverityItem>("{0}");

    instance().setThreshold(Severity::Warning);

    artec::yal::instance().start();

    YAL_DEBUG << "debug";
    YAL_INFO << "info";
    YAL_WARNING << "warning";
    YAL_ERROR << "error";
    YAL_FATAL << "fatal";

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "WARN \nERROR\nFATAL\n");
}

TEST(yal, checkText)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<TextItem>("{0}");

    instance().setThreshold(Severity::Error);

    artec::yal::instance().start();

    YAL_DEBUG << "debug";
    YAL_INFO << "info";
    YAL_WARNING << "warning";
    YAL_ERROR << "error";
    YAL_FATAL << "fatal";

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "error\nfatal\n");
}

TEST(yal, checkSeverityAndText)
{
    using namespace artec::yal;

    std::stringstream buf;

    SinkList sinks;
    sinks.push_back(std::make_unique<StdStreamSink>(buf));
    instance().setSinks(sinks);

    instance().getFormatter().setFormat<SeverityItem, TextItem>("{0} {1}");

    instance().setThreshold(Severity::Info);

    artec::yal::instance().start();

    YAL_DEBUG << "debug" << 1;
    YAL_INFO << "info" << 2;
    YAL_WARNING << "warning" << 3;
    YAL_ERROR << "error" << 4;
    YAL_FATAL << "fatal" << 5;

    artec::yal::instance().stop().wait();

    EXPECT_EQ(buf.str(), "INFO  info2\nWARN  warning3\nERROR error4\nFATAL fatal5\n");
}

void stressTest()
{
    const auto start = std::chrono::high_resolution_clock::now();

    artec::yal::instance().start();

    artec::yal::instance().getFormatter().setFormat
        <
            artec::yal::SeverityItem,
            artec::yal::TimezoneItem,
            artec::yal::DateItem,
            artec::yal::TimeItem,
            artec::yal::ThreadItem,
            artec::yal::TextItem,
            artec::yal::PlaceInCodeItem
        >
        ("{0} {1} {2} {3} {4} {5} {6}");

    std::ofstream file("log1.txt");

    artec::yal::SinkList sinks;
    sinks.push_back(std::make_unique<artec::yal::StdStreamSink>(file));
    sinks.push_back(std::make_unique<artec::yal::FileSink>("log2.txt"));
    artec::yal::instance().setSinks(sinks);

    artec::yal::instance().setThreshold(artec::yal::Severity::Debug);

    const size_t N = 1000000;

    std::thread t1([N]()
    {
        for (size_t i = 0; i < N; ++i)
        {
            YAL_DEBUG << "test" << "some text" << i << fmt::format("{0}:{1}:{0}", "-----", "===");
        }
    });

    std::thread t2([N]()
    {
        for (size_t i = 0; i < N; ++i)
        {
            YAL_INFO << "test" << "some text" << i << fmt::format("{0}:{1}:{0}", "-----", "===");
        }
    });

    std::thread t3([N]()
    {
        for (size_t i = 0; i < N; ++i)
        {
            YAL_WARNING << "test" << "some text" << i << fmt::format("{0}:{1}:{0}", "-----", "===");
        }
    });

    std::thread t4([N]()
    {
        for (size_t i = 0; i < N; ++i)
        {
            YAL_ERROR << "test" << "some text" << i << fmt::format("{0}:{1}:{0}", "-----", "===");
        }
    });

    std::thread t5([N]()
    {
        for (size_t i = 0; i < N; ++i)
        {
            YAL_FATAL << "test" << "some text" << i << fmt::format("{0}:{1}:{0}", "-----", "===");
        }
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    artec::yal::instance().stop().wait();

    const auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
}

int main(int argc, char* argv[])
{
    artec::yal::instance().stop().wait();

#ifdef YAL_ENABLE_STRESS_TEST
    stressTest();
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
