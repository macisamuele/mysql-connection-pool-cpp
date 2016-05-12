/*
 * ConcreteMySqlConnection.cpp
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */
#include "ConcreteMySqlConnection.h"
#include <config.h>                                     // for QUERY_PROFILING_ON define
#include <cppconn/exception.h>                          // for SQL Exception handling
#include <boost/date_time/posix_time/posix_time.hpp>    // for posix_time definition

using namespace std;
using namespace sql;

/**
 * Instantiate oPreparedStatement (a PreparedStatement).
 * It checks that the MySQL connections is in the right state and searches the
 * prepared statements on the statement cache and if not present insert a new
 * statement with the value defined in iDefaultValue
 * Note that to avoid ambiguities the key associated to the prepared statement
 * is the name of the method itself.
 *
 * NOTE: it looks like a function (is not a function in order to benefit of
 *  __FUNCTION__, __FILE__ and __LINE__ (useful in the logging reporting)
 */
#define initialize_prepared_statement(iDefaultValue, oPreparedStatement, oQuery)        \
        if (!isValid()) {                                                               \
            throw SQLException("The current connection result invalid");                \
        }                                                                               \
        aQuery = iDefaultValue;                                                         \
        if(!isStatementCached(string(__FUNCTION__))) {                                  \
            cacheStatement(string(__FUNCTION__), connection->prepareStatement(aQuery)); \
        }                                                                               \
        MySQL::PreparedStatementSP aPStatement = getStatement(string(__FUNCTION__));

/**
 * PROFILING Macros
 *
 * The macros START_PROFILE and END_PROFILE have to be used inside the same scope (same code blocK)
 * because the functionality powered by is based on some definition of variables that should be accessible
 * at the beginning and and the ending of the profiling.
 * The two macros have a parameter (called x) which will be used inside the logs. As clear the parameter
 * represents also a sort of unique key of the profiling, so it is suggested to use different names
 * for different measures.
 */
// START_PROFILE(x) creates and initialize the underlying variables required for the profiling
#define START_PROFILE(x)                                                                        \
    boost::posix_time::ptime x ## Start = boost::posix_time::microsec_clock::universal_time()

// END_PROFILE(x) evaluate the time interval with a millisecond precision and print it using the LOG_PROFILE macro
#define END_PROFILE(x)                                                                              \
        boost::posix_time::ptime x ## Stop = boost::posix_time::microsec_clock::universal_time();   \
        boost::posix_time::time_period x ## TimePeriod(x ## Start, x ## Stop);                      \
        boost::posix_time::time_duration x ## TimeDuration = x ## TimePeriod.length();              \
        logger->log(LLOG_INFO, "Profiling: " #x " - %.3f ms", getTablesTimeDuration.total_microseconds()/1000.0);


#ifdef QUERY_PROFILER_ON
# define START_QUERY_PROFILE(x) START_PROFILE(x)
# define END_QUERY_PROFILE(x, aReturnedValue) END_PROFILE(x); return aReturnedValue
#else
# define START_QUERY_PROFILE(x)
# define END_QUERY_PROFILE(x, aReturnedValue) return aReturnedValue
#endif

namespace macisamuele {

ConcreteMySqlConnection::ConcreteMySqlConnection(const MySQL::MySqlConfig& iConfiguration) : MySQL::MySqlConnection(iConfiguration) {
    CONSTRUCTOR(this);
}
ConcreteMySqlConnection::ConcreteMySqlConnection(const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration) : MySQL::MySqlConnection(iMySqlCache, iConfiguration) {
    CONSTRUCTOR(this);
}
ConcreteMySqlConnection::ConcreteMySqlConnection(const Logger::LoggerSP& iLogger, const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration) : MySQL::MySqlConnection(iLogger, iMySqlCache, iConfiguration) {
    CONSTRUCTOR(this);
}

ConcreteMySqlConnection::~ConcreteMySqlConnection() {
    DESTRUCTOR(this);
}


bool ConcreteMySqlConnection::getTables(vector<string>& oList) {
    START_QUERY_PROFILE(getTables);
    string aQuery;
    try {
        initialize_prepared_statement("SELECT CONCAT(TABLE_SCHEMA, '.', TABLE_NAME) AS TABLES FROM TABLES;", aPStatement, aQuery);
        aPStatement->execute();

        ResultSet* aResultSet = aPStatement->getResultSet();
        if (aResultSet == NULL || !aResultSet->next()) {
            logger->log(LLOG_WARNING, "Empty Result Set for the query: %s", aQuery.c_str());
            END_QUERY_PROFILE(getTables, false);
        }

        vector<MySQL::ResultMap> aResult;
        ResultSetToVector(aResultSet, aResult);

        for (vector<MySQL::ResultMap>::iterator it = aResult.begin(); it != aResult.end(); it++) {
            oList.push_back((*it).find("TABLES")->second);
        }

        aResultSet->close();
        delete aResultSet;

        END_QUERY_PROFILE(getTables, true);
    } catch (const sql::SQLException& aException) {
        logger->log(LLOG_WARNING, "SQLException: Query: %s Error[%s] ErrorCode[%d] State[%s]", aQuery.c_str(), aException.what(), aException.getErrorCode(), aException.getSQLStateCStr());
    }
    END_QUERY_PROFILE(getTables, false);
}

} /* namespace macisamuele */
