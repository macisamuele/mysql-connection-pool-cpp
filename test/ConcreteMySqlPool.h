/*
 * ConcreteMySqlPool.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_CONCRETEMYSQLPOOL_H_
#define TEST_CONCRETEMYSQLPOOL_H_

#include "../src/macisamuele/resource/ResourcePool.h"
#include "../src/macisamuele/mysql/MySqlConfig.h"

namespace test {
namespace macisamuele {
namespace resource {

class ConcreteMySqlPool: public ::macisamuele::Resource::ResourcePool {
public:
    ConcreteMySqlPool(size_t iPoolSize, const ::macisamuele::MySQL::MySqlConfig& iConfiguration) :
        ::macisamuele::Resource::ResourcePool(iPoolSize, ConcreteMySqlConnection::GetFactory(iConfiguration)) { //eventually pass a specific Orange::Logger (shared pointer)
    }

    virtual ~ConcreteMySqlPool() {
    }
};

} /* namespace resource */
} /* namespace macisamuele */
} /* namespace test */

#endif /* TEST_CONCRETEMYSQLPOOL_H_ */
