/*
 * ConcreteMySqlFactory.h
 *
 *  Created on: May 1, 2016
 *      Author: samuele
 */

#ifndef TEST_MYSQLFACTORY_H_
#define TEST_MYSQLFACTORY_H_

#include "src/macisamuele/resource/ResourceFactory.h"       // for ResourceFactory and Resource definition
#include "src/macisamuele/MemoryTracer.h"                   // for memory tracing macros definition
#include "src/macisamuele/logger/Logger.h"                  // for Logger definition
#include "src/macisamuele/cache/Cache.h"                    // for Cache definition
#include "src/macisamuele/mysql/MySqlConfig.h"              // for MySqlConfig definition
#include "src/macisamuele/mysql/MySqlConnection.h"          // for MySqlCacheSP definition
#include "src/macisamuele/MemoryTracer.h"                   // for memory tracing macros definition

namespace macisamuele {

class ConcreteMySqlFactory: public Resource::ResourceFactory {
private:
    const MySQL::MySqlConfig configuration;
    MySQL::MySqlCacheSP statementCache;
    Logger::LoggerSP logger;
public:
    ConcreteMySqlFactory(const MySQL::MySqlConfig& iConfiguration);
    ConcreteMySqlFactory(const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration);
    ConcreteMySqlFactory(const Logger::LoggerSP& iLogger, const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration);
    virtual ~ConcreteMySqlFactory();
    virtual Resource::ResourceSP create();
};
SP_TYPE(ConcreteMySqlFactory);

} /* namespace macisamuele */

#endif /* TEST_MYSQLFACTORY_H_ */
