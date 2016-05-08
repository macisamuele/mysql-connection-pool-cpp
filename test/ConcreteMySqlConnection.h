/*
 * ConcreteMySqlConnection.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_CONCRETEMYSQLCONNECTION_H_
#define TEST_CONCRETEMYSQLCONNECTION_H_

#include "../src/macisamuele/mysql/MySqlConnection.h"
#include "../src/macisamuele/resource/ResourceInterface.h"

namespace test {
namespace macisamuele {
namespace resource {

class ConcreteMySqlConnection: public ::macisamuele::MySQL::MySqlConnection {
public:
    ConcreteMySqlConnection(const ::macisamuele::MySQL::MySqlConfig& iMySQLConfig) :
        ::macisamuele::MySQL::MySqlConnection(iMySQLConfig) {  //eventually pass a specific Orange::Logger (shared pointer)
    }

    virtual ~ConcreteMySqlConnection() {
    }

    ::macisamuele::Resource::ResourceInterfaceSP getResourceInterface() {
        return resourceInterface;
    }

    static ::macisamuele::Resource::ResourceFactorySP GetFactory(const ::macisamuele::MySQL::MySqlConfig& iConfiguration) {
        return boost::shared_ptr< ::macisamuele::Resource::ResourceFactory>(new ConcreteMySqlConnection(iConfiguration));
    }
private:
    ::macisamuele::Resource::ResourceInterfaceSP resourceInterface; //TODO: how to manage the resource interface?
};

} /* namespace resource */
} /* namespace macisamuele */
} /* namespace test */

#endif /* TEST_CONCRETEMYSQLCONNECTION_H_ */
