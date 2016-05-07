/*
 * TypenameDefinitions.h
 *
 *  Created on: May 7, 2016
 *      Author: Samuele Maci <macisamuele@gmail.com>
 */

#ifndef TYPENAME_DEFINITIONS_H_
#define TYPENAME_DEFINITIONS_H_

#include <boost/shared_ptr.hpp>                 // for shared pointer definition

#define SP_TYPE(type) typedef boost::shared_ptr<type> type ## SP
#define SP_NAMESPACE_TYPE(nameSpace, type) typedef boost::shared_ptr<nameSpace::type> type ## SP

#endif /* TYPENAME_DEFINITIONS_H_ */
