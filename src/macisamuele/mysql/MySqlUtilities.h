/*
 * MySqlUtilities.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef MYSQL_MYSQLUTILITIES_H_
#define MYSQL_MYSQLUTILITIES_H_

#include <vector>                           // for std::vector definition
#include <cppconn/resultset.h>              // for sql::ResultSet definition
#include "../resource/ResourceInterface.h"  // for ResoureInterface definition
#include "../logger/Logger.h"               // for Logger definition
#include "../MemoryTracer.h"                // for memory tracing macros definition

namespace macisamuele {
namespace MySQL {

typedef std::pair<std::string, int> ColumnNameIndex;
typedef std::map<std::string, std::string> ResultMap;

class MySqlUtilities {
public:
    MySqlUtilities();
    virtual ~MySqlUtilities();

    /**
     * Utilities required for the management of the resource pool and conversions utilities
     */
protected:
    Logger::LoggerSP logger;
    /**
     * Extracts from the result set the associations between the column name and the column index
     */
    static std::vector<ColumnNameIndex> GetColumnIndexes(sql::ResultSet* iResultSet);

    /**
     * Extract all the columns indicated in iColumnIndexes from the current row on the iResultset.
     * The output storage is represented by the oOutput map (it is cleaned if iClearMap is set to true).
     */
    static void ResultSetRowToMap(std::vector<ColumnNameIndex> iColumnIndexes, sql::ResultSet* iResultSet, ResultMap& oOutput, bool iClearMap = true);

    /**
     * Extract all the columns from the current row on the iResultset.
     * The output storage is represented by the oOutput map (it is cleaned if iClearMap is set to true).
     */
    static void ResultSetRowToMap(sql::ResultSet* iResultSet, ResultMap& oOutput, bool iClearMap = true);

    /**
     * Extract all the result set to a vector of maps. Each item of the vector represents one row of the result.
     * The extracted columns are the columns defined by iColumnIndexes.
     * The output storage is represented by the oOutput vector (it is cleaned if iClearVector is set to true).
     */
    static void ResultSetToVector(std::vector<ColumnNameIndex> iColumnIndexes, sql::ResultSet* iResultSet, std::vector<ResultMap>& oOutput, bool iClearVector = true);

    /**
     * Extract all the result set to a vector of maps. Each item of the vector represents one row of the result.
     * The output storage is represented by the oOutput vector (it is cleaned if iClearVector is set to true).
     */
    static void ResultSetToVector(sql::ResultSet* iResultSet, std::vector<ResultMap>& oOutput, bool iClearVector = true);

};

} /* namespace MySQL */
} /* namespace macisamuele */

#endif /* MYSQL_MYSQLUTILITIES_H_ */
