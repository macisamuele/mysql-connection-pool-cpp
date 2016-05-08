/*
 * ResourcePool.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef MACISAMUELE_RESOURCE_RESOURCEPOOL_H_
#define MACISAMUELE_RESOURCE_RESOURCEPOOL_H_

#include <deque>                    // for queue definition (uniforms the use of the resources)
#include <set>                      // for set definition (collecting the allocated resources)
#include <boost/thread/mutex.hpp>   // for lock feature
#include <exception>                // for exception handling
#include "ResourceFactory.h"        // for ResourceFactory definition
#include "Resource.h"               // for Resource definition
#include "ResourcePoolStat.h"       // for ResourcePoolStats definition
#include "../logger/Logger.h"       // for Logger definition

namespace macisamuele {
namespace Resource {

class ResourcePool {
public:
    size_t getResourcesAcquired();
    size_t getResourcesAvailable();
    size_t getPoolSize();
    ResourcePoolStats getStatistics();
    ResourcePool(size_t iPoolSize, const ResourceFactorySP& iFactory);
    ResourcePool(const Logger::LoggerSP& iLogger, size_t iPoolSize, const ResourceFactorySP& iFactory);

    virtual ~ResourcePool();

    /**
     * Acquire a resource for a temporary use
     *
     * When done, either:
     *      (a) call release() to immediately release it
     *      (b) just let it go out of scope. This will cause it to
     *          automatically be released
     * @throws ResourceUnavailable if is not possible to allocate a new resource
     * @returns a boost::shared_ptr to the resource
     */
    virtual ResourceSP acquire();

    /**
     * Release a connection
     *
     * @param iResourceSP a resource to be released
     */
    void release(ResourceSP iResourceSP);

protected:
    ResourceFactorySP factory;
    size_t poolSize;
    size_t instantiatedResources;
    std::deque<ResourceSP> resourcePool;
    std::set<ResourceSP> aquiredResources;
    boost::mutex lock;
    Logger::LoggerSP logger;
};

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* MACISAMUELE_RESOURCE_RESOURCEPOOL_H_ */
