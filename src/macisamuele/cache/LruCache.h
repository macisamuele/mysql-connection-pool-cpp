/*
 * LruCache.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef CACHE_LRUCACHE_H_
#define CACHE_LRUCACHE_H_

#include "Cache.h"          // for Cache definition
#include <sys/types.h>      // for size_t definition
#include <deque>            // for std::deque (queue) definition
#include <map>              // for std::map definition
#include <set>              // for std::set definition

namespace macisamuele {
namespace Cache {

template<typename CacheKey, typename CachedType>
class LruCache: public Cache<CacheKey, CachedType> {
    typedef typename std::deque<CacheKey>::iterator CacheKeyIterator;
private:
    std::map<CacheKey, CachedType> cacheMemory;
    std::deque<CacheKey> orderedMemory;
    size_t size;

    /**
     * Move the iKey in the most recent used key.
     * NOTE: the key MUST exists on the cache
     */
    virtual void updateUse(const CacheKey& iKey) {
        CacheKeyIterator aIterator;
        // aDequeIterator will never be orderedMemory.end() since the key is present on the cacheMemory
        for (aIterator = orderedMemory.begin(); *aIterator != iKey; aIterator++) {
        }
        orderedMemory.erase(aIterator);
        orderedMemory.push_front(iKey);
    }
public:
    LruCache(size_t iSize) :
            size(iSize) {
    }

    virtual ~LruCache() {
    }

    virtual bool isInCache(const CacheKey& iKey) {
        return cacheMemory.find(iKey) != cacheMemory.end();
    }

    virtual bool tryGetEntry(const CacheKey& iKey, CachedType& oValue) {
        if (!isInCache(iKey)) {
            return false;
        }
        updateUse(iKey);
        oValue = cacheMemory[iKey];
        return true;
    }

    virtual void insert(const CacheKey& iKey, const CachedType& iValue) {
        if (isInCache(iKey)) {   // if the key is in cache the value should be updated and moved in the most recently used
            cacheMemory[iKey] = iValue;
            updateUse(iKey);
        } else {
            if (cacheMemory.size() == size) { // if the cache is full the least element will be deleted
                CacheKey aKey = orderedMemory.back();
                orderedMemory.pop_back();
                cacheMemory.erase(cacheMemory.find(aKey));
            }
            orderedMemory.push_front(iKey);
            cacheMemory[iKey] = iValue;
        }
    }
};

} /* namespace Cache */
} /* namespace macisamuele */

#endif /* CACHE_LRUCACHE_H_ */
