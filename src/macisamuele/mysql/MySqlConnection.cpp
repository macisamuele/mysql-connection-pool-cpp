/*
 * MySqlConnector.cpp
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#include "MySqlConnection.h"

#include <cppconn/driver.h>                     // for sql::Driver definition
#include "../cache/LruCache.h"                  // for LruCache definition
#include "../resource/ResourceUnavailable.h"    // for Resource Unavailable definition
#include "../logger/StderrLogger.h"             // for StderrLogger definition
#include <boost/assert.hpp>                     // for assert definition

namespace macisamuele {
namespace MySQL {

SP_NAMESPACE_TYPE(sql, PreparedStatement);
SP_NAMESPACE_TYPE(sql, Connection);

typedef Cache::Cache<std::string, PreparedStatementSP> MySqlCache;
SP_TYPE(MySqlCache);

MySqlConnection::MySqlConnection(const MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(new Cache::LruCache<std::string, PreparedStatementSP>(10)), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
	logger->log(LLOG_TRACE, "MySqlConnection: Allocated New Object");
}
MySqlConnection::MySqlConnection(const MySqlCacheSP& iMySqlCache, const MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(iMySqlCache), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
	logger->log(LLOG_TRACE, "MySqlConnection: Allocated New Object");
}
MySqlConnection::MySqlConnection(const Logger::LoggerSP& iLogger, const MySqlCacheSP& iMySqlCache, const MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(iMySqlCache), logger(iLogger) {
	logger->log(LLOG_TRACE, "MySqlConnection: Allocated New Object");
}

MySqlConnection::~MySqlConnection() {
	logger->log(LLOG_TRACE, "MySqlConnection: Release Memory");
    if (isValid()) {
        this->connection->close();
    }
}

macisamuele::Resource::ResourceSP MySqlConnection::create() {
    //WARNING: the method is not thread safe!
    sql::Connection *aConnection = get_driver_instance()->connect(configuration.getServer(), configuration.getUsername(), configuration.getPassword());
    if (aConnection == NULL) {
        throw macisamuele::Resource::ResourceUnavailable("MySQL Connection Error");
    }
    aConnection->setSchema(configuration.getSchema());
    this->connection = boost::shared_ptr<sql::Connection>(aConnection);
    return boost::static_pointer_cast<MySqlConnection>(boost::shared_ptr<MySqlConnection>(this));
}

bool MySqlConnection::isStatementCached(const std::string& iName) {
    return statementCache->isInCache(iName);
}

bool MySqlConnection::cacheStatement(const std::string& iName, sql::PreparedStatement* iPreparedStatement) {
    return cacheStatement(iName, boost::shared_ptr<sql::PreparedStatement>(iPreparedStatement));
}

bool MySqlConnection::cacheStatement(const std::string& iName, const PreparedStatementSP iPreparedStatement) {
    statementCache->insert(iName, iPreparedStatement);
    return true;
}

PreparedStatementSP MySqlConnection::getStatement(const std::string& iName) {
    return statementCache->getEntry(iName);
}

bool MySqlConnection::isValid() {
    return this->connection && !this->connection->isClosed();
}
ConnectionSP MySqlConnection::getConnection() {
    BOOST_ASSERT(isValid());
    return this->connection;
}

} /* namespace MySQL */
} /* namespace macisamuele */
