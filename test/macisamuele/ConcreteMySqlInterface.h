/*
 * ConcreteMySqlConnection.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_CONCRETEMYSQLINTERFACE_H_
#define TEST_CONCRETEMYSQLINTERFACE_H_

#include <vector>                                         // for std::vector definition
#include "src/macisamuele/mysql/MySqlInterface.h"         // for MySqlInterface definition
#include "src/macisamuele/mysql/MySqlConnection.h"        // for MySqlConnection definition
#include "src/macisamuele/MemoryTracer.h"                 // for memory tracing macros definition

namespace macisamuele {

class ConcreteMySqlInterface: public MySQL::MySqlInterface {
public:
    ConcreteMySqlInterface(const MySQL::MySqlConnectionSP& iConnection);
    virtual ~ConcreteMySqlInterface();
    bool getTables(std::vector<std::string>& oList);
};
SP_TYPE(ConcreteMySqlInterface);

} /* namespace macisamuele */

#endif /* TEST_CONCRETEMYSQLINTERFACE_H_ */
