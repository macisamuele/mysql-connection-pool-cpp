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

ConnectionSP initConnection(const MySqlConfig& iConfiguration) {
    sql::Connection *aConnection = get_driver_instance()->connect(iConfiguration.getServer(), iConfiguration.getUsername(), iConfiguration.getPassword());
    if (aConnection == NULL) {
        throw macisamuele::Resource::ResourceUnavailable("MySQL Connection Error");
    }
    aConnection->setSchema(iConfiguration.getSchema());
    return boost::shared_ptr<sql::Connection>(aConnection);
}

MySqlConnection::MySqlConnection(const MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(new Cache::LruCache<std::string, PreparedStatementSP>(10)), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
    CONSTRUCTOR(this);
    logger->log(LLOG_TRACE, "MySqlConnection: Allocated New Object");
    this->connection = initConnection(configuration);
}
MySqlConnection::MySqlConnection(const MySqlCacheSP& iMySqlCache, const MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(iMySqlCache), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
    CONSTRUCTOR(this);
    logger->log(LLOG_TRACE, "MySqlConnection: Allocated New Object");
    this->connection = initConnection(configuration);
}
MySqlConnection::MySqlConnection(const Logger::LoggerSP& iLogger, const MySqlCacheSP& iMySqlCache, const MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(iMySqlCache), logger(iLogger) {
    CONSTRUCTOR(this);
    logger->log(LLOG_TRACE, "MySqlConnection: Allocated New Object");
    this->connection = initConnection(configuration);
}

MySqlConnection::~MySqlConnection() {
    DESTRUCTOR(this);
    if (isValid()) {
        this->connection->close();
    }
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
