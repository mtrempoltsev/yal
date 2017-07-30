#pragma once

#include <fstream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace artec
{
    namespace yal
    {
        class AbstractSink
        {
        public:
            virtual ~AbstractSink() noexcept;

            virtual void writeEntryItem(const std::string& text) = 0;
            virtual void addSeparator() = 0;
            virtual void endOfEntry() = 0;
            virtual void flush() = 0;
        };

        using SinkList = std::vector<std::unique_ptr<AbstractSink>>;

        class StdStreamSink final
            : public AbstractSink
        {
        public:
            explicit StdStreamSink(std::ostream& stream) noexcept;

            void writeEntryItem(const std::string& text) override;
            void addSeparator() override;
            void endOfEntry() override;
            void flush() override;

        private:
            std::ostream& stream_;
        };

        class FileSink final
            : public AbstractSink
        {
        public:
            explicit FileSink(const std::string& fileName);

            void writeEntryItem(const std::string& text) override;
            void addSeparator() override;
            void endOfEntry() override;
            void flush() override;

        private:
            std::ofstream file_;
        };
    }
}
