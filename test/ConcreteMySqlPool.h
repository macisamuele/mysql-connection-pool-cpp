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

namespace test {
namespace macisamuele {
namespace Resource {

class ConcreteMySqlPool: public ::macisamuele::Resource::ResourcePool {
public:
    ConcreteMySqlPool(size_t iPoolSize, const ::macisamuele::MySQL::MySqlConfig& iConfiguration) :
        ::macisamuele::Resource::ResourcePool(iPoolSize, ConcreteMySqlConnection::GetFactory(iConfiguration)) { //eventually pass a specific Orange::Logger (shared pointer)
    }

    virtual ~ConcreteMySqlPool() {
    }
};

} /* namespace Resource */
} /* namespace macisamuele */
} /* namespace test */

#endif /* TEST_CONCRETEMYSQLPOOL_H_ */
