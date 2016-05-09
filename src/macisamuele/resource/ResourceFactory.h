/*
 * ResourceFactory.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef RESOURCE_RESOURCEFACTORY_H_
#define RESOURCE_RESOURCEFACTORY_H_

#include "Resource.h"                   // for Resource definition
#include "../TypenameDefinitions.h"     // for SP typed definition
#include "../MemoryTracer.h"            // for memory tracing macros definition

namespace macisamuele {
namespace Resource {

class ResourceFactory {

public:
    virtual ~ResourceFactory() {
        DESTRUCTOR(this);
    }

    virtual ResourceSP create()=0;
};
SP_TYPE(ResourceFactory);

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* RESOURCE_RESOURCEFACTORY_H_ */
