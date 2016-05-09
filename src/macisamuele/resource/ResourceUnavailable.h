/*
 * ResourceUnavailable.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef RESOURCE_RESOURCEUNAVAILABLE_H_
#define RESOURCE_RESOURCEUNAVAILABLE_H_

#include <stdexcept>            // for std::runtime_error definition
#include "../MemoryTracer.h"    // for memory tracing macros definition

namespace macisamuele {
namespace Resource {

class ResourceUnavailable: std::runtime_error {
public:
    ResourceUnavailable() :
            std::runtime_error("Unable to allocate a resource") {
        CONSTRUCTOR(this);
    }
    ResourceUnavailable(const std::string& iMessage) :
            std::runtime_error(iMessage) {
        CONSTRUCTOR(this);
    }
};

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* RESOURCE_RESOURCEUNAVAILABLE_H_ */
