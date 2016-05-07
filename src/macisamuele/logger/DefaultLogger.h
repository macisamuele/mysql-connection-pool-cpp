/*
 * DefaultLogger.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef LOGGER_DEFAULTLOGGER_H_
#define LOGGER_DEFAULTLOGGER_H_

#include "Logger.h"         //for Logger definition
#include <map>              // for std::map definition
#include <string>           // for std::string definition

namespace macisamuele {
namespace Logger {

/*
 * Concrete implementation of a logger which propagates the information on the stderr stream
 */
class DefaultLogger : public Logger {
public:
    DefaultLogger();
    virtual ~DefaultLogger();
    void log(int iLevel, const std::string& iLocation, const char * iMessage, ...);
private:
    std::map<int, std::string> logStringMap;

};

SP_TYPE(DefaultLogger);

} /* namespace Logger */
} /* namespace macisamuele */

#endif /* LOGGER_DEFAULTLOGGER_H_ */
