/*
 * MySqlConnector.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef MYSQL_MYSQLCONNECTOR_H_
#define MYSQL_MYSQLCONNECTOR_H_

#include "../resource/Resource.h"           // for Resource definition
#include "../resource/ResourceFactory.h"    // for ResourceFactory definition
#include "MySqlConfig.h"                    // for MySqlConfig definition
#include "../logger/Logger.h"               // for Logger definition
#include <cppconn/prepared_statement.h>     // for sql::PreparedStatement definition

namespace macisamuele {
namespace MySQL {

SP_NAMESPACE_TYPE(sql, PreparedStatement);
SP_NAMESPACE_TYPE(sql, Connection);

template<typename CacheType>
class MySQLConnection: public Resource::ResourceFactory, public Resource::Resource {

public:
    MySQLConnection(const MySqlConfig& iConfiguration);
    MySQLConnection(const Logger::LoggerSP& iLogger, const MySqlConfig& iConfiguration);

    ~MySQLConnection();

    macisamuele::Resource::ResourceSP create();

    bool isStatementCached(const std::string& iName);

    bool cacheStatement(const std::string& iName, sql::PreparedStatement* iPreparedStatement);

    bool cacheStatement(const std::string& iName, const PreparedStatementSP iPreparedStatement);

    PreparedStatementSP getStatement(const std::string& iName);

    bool isValid();

protected:
    const MySqlConfig configuration;

    /**
     * connection represents the MySQL communication object, it is initialized from the constructor and never set to NULL.
     * At most it could be "manually" deconnected. NULL check will be useless around the code.
     */
    ConnectionSP connection;

    /**
     * Cache of all the statements that are created by the code. It will reduce the overhead due to the creation of the statements
     * and improve the reutilization of the DB level caching.
     * NOTE: the cache will never remove items until its disruption, so the in cache insertion has to guarantee a "limited" number of entries
     */
    CacheType statementCache;

private:
    Logger::LoggerSP logger;
};

} /* namespace MySQL */
} /* namespace macisamuele */

#endif /* MYSQL_MYSQLCONNECTOR_H_ */
