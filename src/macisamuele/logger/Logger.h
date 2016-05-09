/*
 * Logger.h
 *
 *  Created on: May 7, 2016
 *      Author: Samuele Maci <macisamuele@gmail.com>
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>                               // for std::string definition
#include <syslog.h>                             // for LOG_* definition
#include <boost/preprocessor/stringize.hpp>     // for toString on the preprocessor level
#include "../TypenameDefinitions.h"             // for SP typed definition
#include "../MemoryTracer.h"                    // for memory tracing macros definition

#define AT __FILE__ ":" BOOST_PP_STRINGIZE(__LINE__)

#ifndef LOG_TRACE
#   define LOG_TRACE 8 //LOG_DEBUG+1
#endif

#ifndef LLOG_EMERG
#   define LLOG_EMERG LOG_EMERG, AT
#endif /* LLOG_EMERG */
#ifndef LLOG_ALERT
#   define LLOG_ALERT LOG_ALERT, AT
#endif /* LLOG_ALERT */
#ifndef LLOG_CRIT
#   define LLOG_CRIT LOG_CRIT, AT
#endif /* LLOG_CRIT */
#ifndef LLOG_ERR
#   define LLOG_ERR LOG_ERR, AT
#endif /* LLOG_ERR */
#ifndef LLOG_WARNING
#   define LLOG_WARNING LOG_WARNING, AT
#endif /* LLOG_WARNING */
#ifndef LLOG_NOTICE
#   define LLOG_NOTICE LOG_NOTICE, AT
#endif /* LLOG_NOTICE */
#ifndef LLOG_INFO
#   define LLOG_INFO LOG_INFO, AT
#endif /* LLOG_INFO */
#ifndef LLOG_DEBUG
#   define LLOG_DEBUG LOG_DEBUG, AT
#endif /* LLOG_DEBUG */
#ifndef LLOG_TRACE
#   define LLOG_TRACE LOG_TRACE, AT
#endif /* LLOG_TRACE */

namespace macisamuele {
namespace Logger {

/**
 * Generic Logger class
 */
class Logger {
public:
    virtual ~Logger() {
        DESTRUCTOR(this);
    }

    /**
     * Triggers the logging activity.
     *
     * @params iLevel log level used (should be LOG_* as defined in syslog.h)
     * @params iLocation location to be reported (structure suggested __FILE__":"__LINE__
     * @params iMessage log message (format similar to standard printf of the CC)
     * @params ... parameters used by the format string
     */
    virtual void log(int iLevel, const std::string& iLocation, const char * iMessage, ...)=0;

    template<typename T>
    static boost::shared_ptr<T> GetLogger() {
        return boost::shared_ptr<T>(new T());
    }
};

SP_TYPE(Logger);

} /* namespace Logger */
} /* namespace macisamuele */

#endif /* LOGGER_LOGGER_H_ */
