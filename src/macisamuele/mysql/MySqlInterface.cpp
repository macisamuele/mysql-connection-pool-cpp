/*
 * MySqlInterface.cpp
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#include "MySqlInterface.h"
#include <cppconn/resultset_metadata.h>     // for sql::ResultSetMetaData definition
#include "../logger/StderrLogger.h"         // for StderrLogger definition

// check the general validity of a result set
#define assert_valid_result_set(iResultSet)    \
        assert(iResultSet &&                   \
                !iResultSet->isClosed() &&     \
                !iResultSet->isBeforeFirst()   \
                && !iResultSet->isAfterLast())

namespace macisamuele {
namespace MySQL {

MySqlInterface::MySqlInterface(const MySqlConnectionSP& iConnection) :
        connection(iConnection), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
    CONSTRUCTOR(this);
}

MySqlInterface::MySqlInterface(const Logger::LoggerSP& iLogger, const MySqlConnectionSP& iConnection) :
        connection(iConnection), logger(iLogger) {
    CONSTRUCTOR(this);
}

MySqlInterface::~MySqlInterface(){
    DESTRUCTOR(this);
}

std::vector<ColumnNameIndex> MySqlInterface::GetColumnIndexes(sql::ResultSet* iResultSet) {    assert_valid_result_set(iResultSet);
    sql::ResultSetMetaData *aMetadata = iResultSet->getMetaData();
    std::vector<ColumnNameIndex> aColumnIndexes;
    int aColumnCount = aMetadata->getColumnCount();
    for (int i = 1; i <= aColumnCount; i++) {
        ColumnNameIndex aPair(aMetadata->getColumnName(i), i);
        aColumnIndexes.push_back(aPair);
    }
    return aColumnIndexes;
}

void MySqlInterface::ResultSetRowToMap(std::vector<ColumnNameIndex> iColumnIndexes, sql::ResultSet* iResultSet, ResultMap& oOutput, bool iClearMap) {
    assert_valid_result_set(iResultSet);
    if (iClearMap) {
        oOutput.clear();
    }
    for (std::vector<ColumnNameIndex>::iterator it = iColumnIndexes.begin(); it != iColumnIndexes.end(); it++) {
        oOutput[(*it).first] = iResultSet->getString((*it).second);
    }
}

void MySqlInterface::ResultSetRowToMap(sql::ResultSet* iResultSet, ResultMap& oOutput, bool iClearMap) {
    ResultSetRowToMap(GetColumnIndexes(iResultSet), iResultSet, oOutput, iClearMap);
}

void MySqlInterface::ResultSetToVector(std::vector<ColumnNameIndex> iColumnIndexes, sql::ResultSet* iResultSet, std::vector<ResultMap>& oOutput, bool iClearVector) {
    assert_valid_result_set(iResultSet);
    if (iClearVector) {
        oOutput.clear();
    }

    while (iResultSet->next()) {
        ResultMap aMap;
        ResultSetRowToMap(iColumnIndexes, iResultSet, aMap);
        oOutput.push_back(aMap);
    }
}

void MySqlInterface::ResultSetToVector(sql::ResultSet* iResultSet, std::vector<ResultMap>& oOutput, bool iClearVector) {
    ResultSetToVector(GetColumnIndexes(iResultSet), iResultSet, oOutput, iClearVector);
}

} /* namespace MySQL */
} /* namespace macisamuele */
