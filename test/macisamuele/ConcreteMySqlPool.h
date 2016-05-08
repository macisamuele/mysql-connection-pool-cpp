/*
 * ConcreteMySqlPool.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_CONCRETEMYSQLPOOL_H_
#define TEST_CONCRETEMYSQLPOOL_H_

#include "../src/macisamuele/resource/ResourcePool.h"       // for ResourcePool definition
#include "../src/macisamuele/mysql/MySqlConfig.h"           // for MySqlConfig definition
#include "ConcreteMySqlConnection.h"                        // for ConcreteMySqlConnection definition

namespace macisamuele {

class ConcreteMySqlPool: public ::macisamuele::Resource::ResourcePool {
public:
    ConcreteMySqlPool(size_t iPoolSize, const ::macisamuele::MySQL::MySqlConfig& iConfiguration) :
            Resource::ResourcePool(iPoolSize, ConcreteMySqlConnection::GetFactory(iConfiguration)) { //eventually pass a specific Orange::Logger (shared pointer)
    }

    virtual ~ConcreteMySqlPool() {
    }

    ConcreteMySqlConnectionSP acquireConnection() {
        return boost::dynamic_pointer_cast<ConcreteMySqlConnection>(::macisamuele::Resource::ResourcePool::acquire());
    }
};

} /* namespace macisamuele */

#endif /* TEST_CONCRETEMYSQLPOOL_H_ */
