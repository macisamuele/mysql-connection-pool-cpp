/*
 * ConcreteMySqlConnection.cpp
 *
 *  Created on: May 8, 2016
 *      Author: samuele
 */
#include "ConcreteMySqlConnection.h"

namespace macisamuele {

ConcreteMySqlConnection::ConcreteMySqlConnection(const MySQL::MySqlConfig& iMySqlConfig) :
        MySQL::MySqlConnection(iMySqlConfig) {
    resourceInterface = boost::shared_ptr<ConcreteMySqlInterface>(new ConcreteMySqlInterface(boost::shared_ptr<MySQL::MySqlConnection>(this)));
    CONSTRUCTOR(this);
}

ConcreteMySqlConnection::~ConcreteMySqlConnection() {
    DESTRUCTOR(this);
}

::macisamuele::Resource::ResourceInterfaceSP ConcreteMySqlConnection::getResourceInterface() {
    return resourceInterface;
}

ConcreteMySqlInterfaceSP ConcreteMySqlConnection::getInterface() {
    return boost::dynamic_pointer_cast<ConcreteMySqlInterface>(resourceInterface);
}

Resource::ResourceFactorySP ConcreteMySqlConnection::GetFactory(const MySQL::MySqlConfig& iConfiguration) {
    return boost::shared_ptr<ResourceFactory>(new ConcreteMySqlConnection(iConfiguration));
}

} /* namespace macisamuele */
