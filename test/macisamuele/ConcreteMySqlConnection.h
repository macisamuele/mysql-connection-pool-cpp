/*
 * ConcreteMySqlConnection.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_MYSQLCONNETION_H_
#define TEST_MYSQLCONNETION_H_

#include "../../src/macisamuele/mysql/MySqlConnection.h"
#include "../../src/macisamuele/resource/ResourceInterface.h"
#include "../../src/macisamuele/resource/ResourceFactory.h"
#include "ConcreteMySqlInterface.h"

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
