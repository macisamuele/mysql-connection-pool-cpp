/*
 * ConcreteMySqlConnection.h
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */

#ifndef TEST_CONCRETEMYSQLINTERFACE_H_
#define TEST_CONCRETEMYSQLINTERFACE_H_

#include "../../src/macisamuele/mysql/MySqlInterface.h"
#include "../../src/macisamuele/mysql/MySqlConnection.h"
#include <vector>

namespace macisamuele {

class ConcreteMySqlInterface: public ::macisamuele::MySQL::MySqlInterface {
public:
    ConcreteMySqlInterface(const ::macisamuele::MySQL::MySqlConnectionSP& iConnection);
    virtual ~ConcreteMySqlInterface();
    bool getTables(std::vector<std::string>& oList);
};
SP_TYPE(ConcreteMySqlInterface);

} /* namespace macisamuele */

#endif /* TEST_CONCRETEMYSQLINTERFACE_H_ */
