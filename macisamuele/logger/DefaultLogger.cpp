/*
 * DefaultLogger.cpp
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#include "DefaultLogger.h"
#include <iostream>         // for printing on the stderr

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
    return aMap;
}

DefaultLogger::DefaultLogger() :
        logStringMap(initLogStringMap()) {
}

DefaultLogger::~DefaultLogger() {
}

void DefaultLogger::log(int iLevel, const std::string& iLocation, const std::string& iMessage, ...) {
    char aBuffer[BUFFER_SIZE + 1] = { 0 };
    va_list argptr;
    va_start(argptr, iMessage);
    vsprintf(aBuffer, iMessage.c_str(), argptr);
    std::cerr << logStringMap[iLevel] << " | " << iLocation << " | " << aBuffer << std::endl;
}

} /* namespace Logger */
} /* namespace macisamuele */
