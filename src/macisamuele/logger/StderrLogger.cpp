/*
 * StderrLogger.cpp
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#include "StderrLogger.h"
#include <iostream>                                     // for printing on the stderr
#include <cstdarg>                                      // for va_list definition
#include <cstdio>                                       // for vsprintf definition
#include <boost/date_time/posix_time/posix_time.hpp>    // for posix_time definition

#define BUFFER_SIZE 4096

namespace macisamuele {
namespace Logger {

std::map<int, std::string> initLogStringMap() {
    std::map<int, std::string> aMap;
    aMap[LOG_EMERG] = "EMERG";
    aMap[LOG_ALERT] = "ALERT";
    aMap[LOG_CRIT] = "CRIT";
    aMap[LOG_ERR] = "ERR";
    aMap[LOG_WARNING] = "WARNING";
    aMap[LOG_NOTICE] = "NOTICE";
    aMap[LOG_INFO] = "INFO";
    aMap[LOG_DEBUG] = "DEBUG";
    aMap[LOG_TRACE] = "TRACE";
    return aMap;
}

StderrLogger::StderrLogger() :
        logStringMap(initLogStringMap()) {
    CONSTRUCTOR(this);
}

StderrLogger::~StderrLogger() {
    DESTRUCTOR(this);
}

void StderrLogger::log(int iLevel, const std::string& iLocation, const char * iMessage, ...) {
    char aBuffer[BUFFER_SIZE + 1] = { 0 };
    va_list argptr;
    va_start(argptr, iMessage);
    vsprintf(aBuffer, iMessage, argptr);
    std::cerr << boost::posix_time::microsec_clock::local_time() << " | " << logStringMap[iLevel] << " | " << iLocation << " | " << aBuffer << std::endl;
}

} /* namespace Logger */
} /* namespace macisamuele */
