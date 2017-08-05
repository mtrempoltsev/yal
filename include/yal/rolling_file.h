#pragma once

#include <fstream>
#include <list>

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>

#include "abstract_sink.h"

namespace artec
{
    namespace yal
    {
        class RollingFileSink final
            : public AbstractSink
        {
        public:
            RollingFileSink(const std::string& dir, const std::string& filePrefix,
                const std::string& fileSuffix = ".txt", size_t maxFileSize = 512 * 1024, size_t maxNumOfFiles = 32);

            void out(const std::string& text) override;
            void flush() override;

        private:
            void openNewFile();

            void collectIndexes();
            void cleanup();

            boost::filesystem::path getFileName(size_t i) const;
            size_t getNextIndex() const;

        private:
            const boost::filesystem::path dir_;

            const std::string prefix_;
            const std::string suffix_;
            const size_t maxFileSize_;
            const size_t maxNumOfFiles_;

            using SortedIndexes = std::list<size_t>;
            SortedIndexes indexes_;

            boost::filesystem::ofstream file_;
            size_t fileSize_;
        };
    }
}
