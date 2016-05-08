/*
 * ConcreteMySqlConnection.cpp
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#include "ConcreteMySqlInterface.h"
#include <cppconn/exception.h>                             // for sql::Exception definition
#include "../../src/macisamuele/mysql/MySqlConnection.h"   // for boost::shared_ptr<sql::XYZ> types
#include <boost/preprocessor/cat.hpp>

using namespace macisamuele;
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
#define initialize_prepared_statement(iDefaultValue, oPreparedStatement, oQuery)                                    \
    MySQL::MySqlConnectionSP BOOST_PP_CAT(aConnection, __LINE__)  = this->getConnection();                          \
    if (!BOOST_PP_CAT(aConnection, __LINE__) || !BOOST_PP_CAT(aConnection, __LINE__)->isValid()) {                  \
        throw sql::SQLException("The current connection result invalid");                                           \
    }                                                                                                               \
    aQuery = iDefaultValue;                                                                                         \
    if(!BOOST_PP_CAT(aConnection, __LINE__)->isStatementCached(string(__FUNCTION__))) {                             \
    	BOOST_PP_CAT(aConnection, __LINE__)->cacheStatement(string(__FUNCTION__),                                   \
                BOOST_PP_CAT(aConnection, __LINE__)->getConnection()->prepareStatement(aQuery));                    \
    }                                                                                                               \
    MySQL::PreparedStatementSP aPStatement = BOOST_PP_CAT(aConnection, __LINE__)->getStatement(string(__FUNCTION__));

namespace macisamuele {

ConcreteMySqlInterface::ConcreteMySqlInterface(
		const MySQL::MySqlConnectionSP& iConnection) :
		MySqlInterface(iConnection) {
}

ConcreteMySqlInterface::~ConcreteMySqlInterface() {
}

bool ConcreteMySqlInterface::getTables(vector<string>& oList) {
	string aQuery;
	try {
		initialize_prepared_statement(
				"SELECT CONCAT(TABLE_SCHEMA, '.', TABLE_NAME) AS TABLES FROM TABLES;",
				aPStatement, aQuery);
		aPStatement->execute();

		ResultSet* aResultSet = aPStatement->getResultSet();
		if (aResultSet == NULL || !aResultSet->next()) {
			logger->log(LLOG_WARNING, "Empty Result Set for the query: %s", aQuery.c_str());
			return false;
		}

		vector<MySQL::ResultMap> aResult;
		ResultSetToVector(aResultSet, aResult);

		for(vector<MySQL::ResultMap>::iterator it = aResult.begin(); it != aResult.end(); it++) {
			oList.push_back((*it).find("TABLES")->second);
		}

		aResultSet->close();
		delete aResultSet;

		return true;
	} catch (const sql::SQLException& aException) {
		logger->log(LLOG_WARNING,
				"SQLException: Query: %s Error[%s] ErrorCode[%d] State[%s]",
				aQuery.c_str(), aException.what(), aException.getErrorCode(),
				aException.getSQLStateCStr());
	}
	return false;
}

} /* namespace macisamuele */
