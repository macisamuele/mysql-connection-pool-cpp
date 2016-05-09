/*
 * ConcreteMySqlConnection.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_MYSQLCONNETION_H_
#define TEST_MYSQLCONNETION_H_

#include "ConcreteMySqlInterface.h"                       // for ConcreteMySqlInterface definition
#include "src/macisamuele/mysql/MySqlConnection.h"        // for MySqlConnection definition
#include "src/macisamuele/resource/ResourceFactory.h"     // for ResourceFactory, Resource and Resource Interface definition
#include "src/macisamuele/MemoryTracer.h"                 // for memory tracing macros definition

namespace macisamuele {

class ConcreteMySqlConnection: public MySQL::MySqlConnection {
private:
    ConcreteMySqlInterfaceSP resourceInterface; //TODO: how to manage the resource interface?
public:
    ConcreteMySqlConnection(const MySQL::MySqlConfig& iMySqlConfig);
    virtual ~ConcreteMySqlConnection();

    macisamuele::Resource::ResourceInterfaceSP getResourceInterface();

    ConcreteMySqlInterfaceSP getInterface();

    static macisamuele::Resource::ResourceFactorySP GetFactory(const MySQL::MySqlConfig& iConfiguration);
};
SP_TYPE(ConcreteMySqlConnection);

} /* namespace macisamuele */

#endif /* TEST_MYSQLCONNETION_H_ */
