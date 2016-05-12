/*
 * Resource.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef RESOURCE_RESOURCE_H_
#define RESOURCE_RESOURCE_H_

#include "ResourceInterface.h"          // for ResourceInterface definition
#include "../TypenameDefinitions.h"     // for SP typed definition
#include "../MemoryTracer.h"            // for memory tracing macros definition

namespace macisamuele {
namespace Resource {

class Resource {

public:
    virtual ~Resource() {
        DESTRUCTOR(this);
    }
    virtual bool isValid() = 0;

};
SP_TYPE(Resource);

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* RESOURCE_RESOURCE_H_ */
