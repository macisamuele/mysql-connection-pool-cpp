/*
 * MySqlConfig.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef MYSQL_MYSQLCONFIG_H_
#define MYSQL_MYSQLCONFIG_H_

#include "../TypenameDefinitions.h"     // for SP typed definition
#include <boost/lexical_cast.hpp>       // for conversions (string - int)

namespace macisamuele {
namespace MySQL {

class MySqlConfig {
protected:
    std::string host;
    unsigned int port;
    std::string username;
    std::string password;
    std::string schema;

public:

    MySqlConfig() :
            host("localhost"), port(3306), username("root"), password("root"), schema("information_schema") {
    }

    MySqlConfig(const std::string& iHost, unsigned int iPort, const std::string& iUsername, const std::string& iPassword, const std::string& iSchema) :
            host(iHost), port(iPort), username(iUsername), password(iPassword), schema(iSchema) {
    }

    MySqlConfig& operator=(const MySqlConfig& iConfiguration) {
        this->host = iConfiguration.host;
        this->port = iConfiguration.port;
        this->username = iConfiguration.username;
        this->password = iConfiguration.password;
        this->schema = iConfiguration.schema;
        return *(this);
    }

    std::string getServer() const {
        return host + boost::lexical_cast<std::string>(port);
    }

    std::string getUsername() const {
        return username;
    }

    std::string getPassword() const {
        return password;
    }

    std::string getSchema() const {
        return schema;
    }
};
SP_TYPE(MySqlConfig);

} /* namespace MySQL */
} /* namespace macisamuele */

#endif /* MACISAMUELE_MYSQL_MYSQLCONFIG_H_ */
