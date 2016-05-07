/*
 * ResourcePool.cpp
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#include "ResourcePool.h"
#include "../logger/DefaultLogger.h"
#include "ResourceUnavailable.h"

namespace macisamuele {
namespace Resource {

#define SCOPED_LOCK(aLock) boost::mutex::scoped_lock aLock(this->lock)

size_t ResourcePool::getResourcesAcquired() {
    SCOPED_LOCK(aLock);
    // Lock the modification of the resources
    return this->aquiredResources.size();
}

size_t ResourcePool::getResourcesAvailable() {
    return this->poolSize - getResourcesAcquired();
}

size_t ResourcePool::getPoolSize() {
    return this->poolSize;
}

ResourcePoolStats ResourcePool::getStatistics() {
    ResourcePoolStats stats; // collect statistics
    stats.poolSize = this->poolSize;
    stats.resourcesAcquired = this->getResourcesAcquired();
    return stats;
}

ResourcePool::ResourcePool(size_t iPoolSize, const ResourceFactorySP& iFactory) :
        factory(iFactory), poolSize(iPoolSize), instantiatedResources(0), logger(Logger::Logger::GetLogger<Logger::DefaultLogger>()) {
}

ResourcePool::ResourcePool(const Logger::LoggerSP& iLogger, size_t iPoolSize, const ResourceFactorySP& iFactory) :
        factory(iFactory), poolSize(iPoolSize), instantiatedResources(0), logger(iLogger) {
}

ResourcePool::~ResourcePool() { // no need to do nothing because the shared_ptr will delete all the pointers
}

ResourceSP ResourcePool::acquire() {
    SCOPED_LOCK(aLock);
    // Lock the modification of the resources
    ResourceSP aResourceSP;
    if (this->instantiatedResources != this->poolSize) { // is possible to allocate a new resource
        this->logger->log(LLOG_INFO, "Allocated a new resource.");
        aResourceSP = this->factory->create();
        this->instantiatedResources++;
        this->aquiredResources.insert(aResourceSP);
    } else if (this->resourcePool.size() > 0) { // there are available connections
        ResourceSP aResource = this->resourcePool.front();
        this->resourcePool.pop_front();
    }

    if (!aResourceSP) { // if no resource is assigned to the pointer
        throw ResourceUnavailable();
    }

    if (!aResourceSP->isValid()) { // if the resource is not valid try to reinitialize it
        this->logger->log(LLOG_INFO, "Re-init tentative");
        aResourceSP.reset(this->factory->create().get());
    }
    return boost::static_pointer_cast<Resource>(aResourceSP);
}

void ResourcePool::release(ResourceSP iResourceSP) {
    SCOPED_LOCK(aLock);
    // Lock the modification of the resources
    if (this->aquiredResources.erase(iResourceSP) > 0) {
        // if no resources are deleted it means that the resources was no part of the current pool
        this->resourcePool.push_back(iResourceSP);
    }
}

} /* namespace Resource */
} /* namespace macisamuele */
