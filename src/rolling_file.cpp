#include <yal/rolling_file.h>

#include <set>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/operations.hpp>

#include <fmt/format.h>

artec::yal::RollingFileSink::RollingFileSink(const std::string& dir, const std::string& filePrefix,
    const std::string& fileSuffix, size_t maxFileSize, size_t maxNumOfFiles)
    : dir_(dir)
    , prefix_(filePrefix)
    , suffix_(fileSuffix)
    , maxFileSize_(maxFileSize < 512 ? 512 : maxFileSize)
    , maxNumOfFiles_(maxNumOfFiles < 1 ? 1 : maxNumOfFiles)
    , fileSize_(0)
{
    collectIndexes();
    openNewFile();
}

void artec::yal::RollingFileSink::out(const std::string& text)
{
    file_.write(text.c_str(), text.size());
    file_.put('\n');

    fileSize_ += (text.size() + 1);

    if (fileSize_ > maxFileSize_)
    {
        file_.close();
        fileSize_ = 0;
        openNewFile();
    }
}

void artec::yal::RollingFileSink::flush()
{
    file_.flush();
}

void artec::yal::RollingFileSink::openNewFile()
{
    cleanup();

    const auto index = getNextIndex();
    indexes_.push_back(index);

    file_.open(getFileName(index), std::ios::binary);
}

void artec::yal::RollingFileSink::collectIndexes()
{
    const auto prefixLength = prefix_.length();
    const auto prefixAndSuffixLength = prefixLength + suffix_.length();

    std::set<size_t> sortedIndexes;

    for (auto it = boost::filesystem::directory_iterator(dir_),
         end = boost::filesystem::directory_iterator();
         it != end; ++it)
    {
        const auto& entry = *it;
        if (boost::filesystem::is_regular_file(entry))
        {
            const auto name = entry.path().filename().native();
            if (boost::starts_with(name, prefix_) && boost::ends_with(name, suffix_))
            {
                size_t i = 0;

                try
                {
                    const auto indexAsText = name.substr(prefixLength, name.size() - prefixAndSuffixLength);
                    i = std::stol(indexAsText);
                }
                catch (const std::exception&)
                {
                    i = 0;
                }

                if (i != 0)
                {
                    sortedIndexes.insert(i);
                }
            }
        }
    }

    indexes_.assign(sortedIndexes.begin(), sortedIndexes.end());
}

void artec::yal::RollingFileSink::cleanup()
{
    if (indexes_.size() < maxNumOfFiles_)
    {
        return;
    }

    auto it = indexes_.cbegin();
    const auto end = indexes_.cend();

    while (it != end && indexes_.size() >= maxNumOfFiles_)
    {
        boost::system::error_code error;
        boost::filesystem::remove(getFileName(*it), error);

        if (error)
        {
            ++it; // can't delete file. just skip it
        }
        else
        {
            auto toDelete = it++;
            indexes_.erase(toDelete);
        }
    }
}

boost::filesystem::path artec::yal::RollingFileSink::getFileName(size_t i) const
{
    return dir_ / fmt::format("{0}{1}{2}", prefix_, i, suffix_);
}

size_t artec::yal::RollingFileSink::getNextIndex() const
{
    if (indexes_.empty())
    {
        return 1;
    }

    return indexes_.back() + 1;
}
