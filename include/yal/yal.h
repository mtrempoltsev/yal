#pragma once

#include <yal/core.h>

#ifdef YAL_LOGGING_DISABLED
    #define YAL_DEBUG if (true); else artec::yal::EntryMaker(artec::yal::Severity::Debug, __FILE__, __LINE__)
    #define YAL_DEBUG_IF(condition) if (true); else artec::yal::EntryMaker(artec::yal::Severity::Debug, __FILE__, __LINE__)
#else
    #define YAL_DEBUG \
        if (artec::yal::Severity::Debug < artec::yal::instance().threshold()) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Debug, __FILE__, __LINE__)
    #define YAL_DEBUG_IF(condition) \
        if (artec::yal::Severity::Debug < artec::yal::instance().threshold() || !(condition)) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Debug, __FILE__, __LINE__)
#endif

#ifdef YAL_LOGGING_DISABLED
    #define YAL_INFO if (true); else artec::yal::EntryMaker(artec::yal::Severity::Info, __FILE__, __LINE__)
    #define YAL_INFO_IF(condition) if (true); else artec::yal::EntryMaker(artec::yal::Severity::Info, __FILE__, __LINE__)
#else
    #define YAL_INFO \
        if (artec::yal::Severity::Info < artec::yal::instance().threshold()) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Info, __FILE__, __LINE__)
    #define YAL_INFO_IF(condition) \
        if (artec::yal::Severity::Info < artec::yal::instance().threshold() || !(condition)) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Info, __FILE__, __LINE__)
#endif

#ifdef YAL_LOGGING_DISABLED
    #define YAL_WARNING if (true); else artec::yal::EntryMaker(artec::yal::Severity::Warning, __FILE__, __LINE__)
    #define YAL_WARNING_IF(condition) if (true); else artec::yal::EntryMaker(artec::yal::Severity::Warning, __FILE__, __LINE__)
#else
    #define YAL_WARNING \
        if (artec::yal::Severity::Warning < artec::yal::instance().threshold()) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Warning, __FILE__, __LINE__)
    #define YAL_WARNING_IF(condition) \
        if (artec::yal::Severity::Warning < artec::yal::instance().threshold() || !(condition)) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Warning, __FILE__, __LINE__)
#endif

#ifdef YAL_LOGGING_DISABLED
    #define YAL_ERROR if (true); else artec::yal::EntryMaker(artec::yal::Severity::Error, __FILE__, __LINE__)
    #define YAL_ERROR_IF(condition) if (true); else artec::yal::EntryMaker(artec::yal::Severity::Error, __FILE__, __LINE__)
#else
    #define YAL_ERROR \
        if (artec::yal::Severity::Error < artec::yal::instance().threshold()) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Error, __FILE__, __LINE__)
    #define YAL_ERROR_IF(condition) \
        if (artec::yal::Severity::Error < artec::yal::instance().threshold() || !(condition)) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Error, __FILE__, __LINE__)
#endif

#ifdef YAL_LOGGING_DISABLED
    #define YAL_FATAL if (true); else artec::yal::EntryMaker(artec::yal::Severity::Fatal, __FILE__, __LINE__)
    #define YAL_FATAL_IF(condition) if (true); else artec::yal::EntryMaker(artec::yal::Severity::Fatal, __FILE__, __LINE__)
#else
    #define YAL_FATAL \
        artec::yal::EntryMaker(artec::yal::Severity::Fatal, __FILE__, __LINE__)
    #define YAL_FATAL_IF(condition) \
        if (!(condition)) ; \
        else artec::yal::EntryMaker(artec::yal::Severity::Fatal, __FILE__, __LINE__)
#endif
