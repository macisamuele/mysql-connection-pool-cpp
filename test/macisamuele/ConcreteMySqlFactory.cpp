/*
 * ConcreteMySqlFactory.cpp
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */
#include "ConcreteMySqlFactory.h"
#include "ConcreteMySqlConnection.h"        // for ConcreteMySqlConnection, MySQL::PreparedStatementSP, etc definition
#include "src/macisamuele/cache/LruCache.h"              // for LruCache definition
#include "src/macisamuele/logger/StderrLogger.h"         // for StderrLogger definition
#include <boost/assert.hpp>                 // for assert definition

namespace macisamuele {

ConcreteMySqlFactory::ConcreteMySqlFactory(const MySQL::MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(new Cache::LruCache<std::string, MySQL::PreparedStatementSP>(10)), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
    CONSTRUCTOR(this);
}

ConcreteMySqlFactory::ConcreteMySqlFactory(const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(iMySqlCache), logger(Logger::Logger::GetLogger<Logger::StderrLogger>()) {
    CONSTRUCTOR(this);
}
ConcreteMySqlFactory::ConcreteMySqlFactory(const Logger::LoggerSP& iLogger, const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration) :
        configuration(iConfiguration), statementCache(iMySqlCache), logger(iLogger) {
    CONSTRUCTOR(this);
}

ConcreteMySqlFactory::~ConcreteMySqlFactory() {
    DESTRUCTOR(this);
}
Resource::ResourceSP ConcreteMySqlFactory::create() {
    return boost::static_pointer_cast<MySQL::MySqlConnection>(
            boost::shared_ptr<MySQL::MySqlConnection>(
                    new ConcreteMySqlConnection(logger, statementCache, configuration)
            ));
}

} /* namespace macisamuele */
