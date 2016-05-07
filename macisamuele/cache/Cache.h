/*
 * Cache.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef CACHE_CACHE_H_
#define CACHE_CACHE_H_

#include <stdexcept>        // for std::runtime_error definition

namespace macisamuele {
namespace Cache {

class KeyMiss : public std::runtime_error {
public:
    KeyMiss() : std::runtime_error("Key Not Found") {
    }
    KeyMiss(const std::string& iMessage) : std::runtime_error(iMessage) {
    }
};

template<typename CacheKey, typename CachedType>
class Cache {
public:
    virtual ~Cache() {
    }

    /**
     * Check if the key is present on the cache
     *
     * @params iKey key to be found on the cache
     * @params oValue cached object (if present)
     *
     * @returns true if the key exists on the cache, false otherwise
     */
    virtual bool isInCache(const CacheKey& iKey)=0;

    /**
     * Extract the key from the cache and store it on oValue if is the key exists.
     *
     * @params iKey key to be found on the cache
     * @params oValue cached object (if present)
     *
     * @returns true if the key exists on the cache, false otherwise
     */
    virtual bool tryGetEntry(const CacheKey& iKey, CachedType& oValue)=0;

    /**
     * Extract the key from the cache. If the key is not found throws an KeyMiss exception.
     *
     * @params iKey key to be found on the cache
     *
     * @throws KeyMiss error if the key is not present on the cache
     *
     * @returns the cached object
     */
    virtual CachedType getEntry(const CacheKey& iKey) {
        CachedType aCachedObject;
        if(!tryGetEntry(iKey, aCachedObject)) {
            throw KeyMiss();
        }
        return aCachedObject;
    }

    /**
     * Insert a new value on the cache
     *
     * @params iKey key to be found on the cache
     * @params oValue cached object (if present)
     */
    virtual void insert(const CacheKey& iKey, const CachedType& iValue)=0;
};

} /* namespace Cache */
} /* namespace macisamuele */

#endif /* CACHE_CACHE_H_ */
