/*
 * ResourceInterface.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef RESOURCE_RESOURCEINTERFACE_H_
#define RESOURCE_RESOURCEINTERFACE_H_

#include "../TypenameDefinitions.h"     // for SP typed definition
#include "../MemoryTracer.h"            // for memory tracing macros definition

namespace macisamuele {
namespace Resource {

class ResourceInterface {

public:
    virtual ~ResourceInterface() {
        DESTRUCTOR(this);
    }

};
SP_TYPE(ResourceInterface);

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* RESOURCE_RESOURCEINTERFACE_H_ */
