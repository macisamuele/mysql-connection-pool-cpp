/*
 * MySqlConnector.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef MYSQL_MYSQLCONNECTOR_H_
#define MYSQL_MYSQLCONNECTOR_H_

#include <cppconn/prepared_statement.h>         // for sql::PreparedStatement definition
#include <cppconn/connection.h>                 // for sql::Connection definition
#include "../TypenameDefinitions.h"             // for SP typed definition
#include "../resource/Resource.h"               // for Resource definition
#include "../resource/ResourceFactory.h"        // for ResourceFactory definition
#include "../logger/Logger.h"                   // for Logger definition
#include "../cache/Cache.h"                     // for Cache definition
#include "../logger/Logger.h"                   // for Logger definition
#include "MySqlConfig.h"                        // for MySqlConfig definition

namespace macisamuele {
namespace MySQL {

SP_NAMESPACE_TYPE(sql, PreparedStatement);
SP_NAMESPACE_TYPE(sql, Connection);

typedef Cache::Cache<std::string, PreparedStatementSP> MySqlCache;
SP_TYPE(MySqlCache);

class MySqlConnection: public Resource::ResourceFactory, public Resource::Resource {

public:
    MySqlConnection(const MySqlConfig& iConfiguration);
    MySqlConnection(const MySqlCacheSP& iMySqlCache, const MySqlConfig& iConfiguration);
    MySqlConnection(const Logger::LoggerSP& iLogger, const MySqlCacheSP& iMySqlCache, const MySqlConfig& iConfiguration);
    ~MySqlConnection();
    virtual macisamuele::Resource::ResourceSP create();
    virtual bool isStatementCached(const std::string& iName);
    virtual bool cacheStatement(const std::string& iName, sql::PreparedStatement* iPreparedStatement);
    virtual bool cacheStatement(const std::string& iName, const PreparedStatementSP iPreparedStatement);
    virtual PreparedStatementSP getStatement(const std::string& iName);
    virtual bool isValid();
    virtual ConnectionSP getConnection();
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
    MySqlCacheSP statementCache;

    Logger::LoggerSP logger;
};

SP_TYPE(MySqlConnection);

} /* namespace MySQL */
} /* namespace macisamuele */

#endif /* MYSQL_MYSQLCONNECTOR_H_ */
