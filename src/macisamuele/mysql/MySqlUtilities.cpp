/*
 * MySqlUtilities.cpp
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#include "MySqlUtilities.h"
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

MySqlUtilities::MySqlUtilities() {
    CONSTRUCTOR(this);
}
MySqlUtilities::~MySqlUtilities() {
    DESTRUCTOR(this);
}

std::vector<ColumnNameIndex> MySqlUtilities::GetColumnIndexes(sql::ResultSet* iResultSet) {    assert_valid_result_set(iResultSet);
    sql::ResultSetMetaData *aMetadata = iResultSet->getMetaData();
    std::vector<ColumnNameIndex> aColumnIndexes;
    int aColumnCount = aMetadata->getColumnCount();
    for (int i = 1; i <= aColumnCount; i++) {
        ColumnNameIndex aPair(aMetadata->getColumnName(i), i);
        aColumnIndexes.push_back(aPair);
    }
    return aColumnIndexes;
}

void MySqlUtilities::ResultSetRowToMap(std::vector<ColumnNameIndex> iColumnIndexes, sql::ResultSet* iResultSet, ResultMap& oOutput, bool iClearMap) {
    assert_valid_result_set(iResultSet);
    if (iClearMap) {
        oOutput.clear();
    }
    for (std::vector<ColumnNameIndex>::iterator it = iColumnIndexes.begin(); it != iColumnIndexes.end(); it++) {
        oOutput[(*it).first] = iResultSet->getString((*it).second);
    }
}

void MySqlUtilities::ResultSetRowToMap(sql::ResultSet* iResultSet, ResultMap& oOutput, bool iClearMap) {
    ResultSetRowToMap(GetColumnIndexes(iResultSet), iResultSet, oOutput, iClearMap);
}

void MySqlUtilities::ResultSetToVector(std::vector<ColumnNameIndex> iColumnIndexes, sql::ResultSet* iResultSet, std::vector<ResultMap>& oOutput, bool iClearVector) {
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

void MySqlUtilities::ResultSetToVector(sql::ResultSet* iResultSet, std::vector<ResultMap>& oOutput, bool iClearVector) {
    ResultSetToVector(GetColumnIndexes(iResultSet), iResultSet, oOutput, iClearVector);
}

} /* namespace MySQL */
} /* namespace macisamuele */
