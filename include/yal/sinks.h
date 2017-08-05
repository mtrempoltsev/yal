#pragma once

#include <fstream>
#include <memory>
#include <ostream>
#include <vector>

#include "abstract_sink.h"

#ifdef YAL_USES_BOOST
#include "rolling_file.h"
#endif

namespace artec
{
    namespace yal
    {
        using SinkList = std::vector<std::unique_ptr<AbstractSink>>;

        class StdStreamSink final
            : public AbstractSink
        {
        public:
            explicit StdStreamSink(std::ostream& stream) noexcept;

            void out(const std::string& text) override;
            void flush() override;

        private:
            std::ostream& stream_;
        };

        class FileSink final
            : public AbstractSink
        {
        public:
            explicit FileSink(const std::string& fileName);

            void out(const std::string& text) override;
            void flush() override;

        private:
            std::ofstream file_;
        };
    }
}
