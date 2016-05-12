/*
 * ConcreteMySqlConnection.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_MYSQLCONNETION_H_
#define TEST_MYSQLCONNETION_H_

#include "../../src/macisamuele/mysql/MySqlUtilities.h"     // for ConcreteMySqlInterface definition
#include "src/macisamuele/mysql/MySqlConnection.h"          // for MySqlConnection definition
#include "src/macisamuele/resource/ResourceFactory.h"       // for ResourceFactory, Resource and Resource Interface definition
#include "src/macisamuele/MemoryTracer.h"                   // for memory tracing macros definition
#include <vector>                                           // for std::vector definition

namespace macisamuele {

class ConcreteMySqlConnection: public MySQL::MySqlConnection {

public:
    ConcreteMySqlConnection(const MySQL::MySqlConfig& iConfiguration);
    ConcreteMySqlConnection(const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration);
    ConcreteMySqlConnection(const Logger::LoggerSP& iLogger, const MySQL::MySqlCacheSP& iMySqlCache, const MySQL::MySqlConfig& iConfiguration);
    virtual ~ConcreteMySqlConnection();

    bool getTables(std::vector<std::string>& oList);

};
SP_TYPE(ConcreteMySqlConnection);

} /* namespace macisamuele */

#endif /* TEST_MYSQLCONNETION_H_ */
