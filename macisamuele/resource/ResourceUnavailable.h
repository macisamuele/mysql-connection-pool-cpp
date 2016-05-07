/*
 * ResourceUnavailable.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef RESOURCE_RESOURCEUNAVAILABLE_H_
#define RESOURCE_RESOURCEUNAVAILABLE_H_

namespace macisamuele {
namespace Resource {

class ResourceUnavailable: std::runtime_error {
public:
    ResourceUnavailable(const std::string& iMessage = "Unable to allocate a resource") :
            std::runtime_error(iMessage) {
    }
};

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* RESOURCE_RESOURCEUNAVAILABLE_H_ */
