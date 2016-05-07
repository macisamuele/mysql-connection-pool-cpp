/*
 * ResourcePoolStat.h
 *
 *  Created on: May 7, 2016
 *      Author: samuele
 */

#ifndef RESOURCE_RESOURCEPOOLSTAT_H_
#define RESOURCE_RESOURCEPOOLSTAT_H_

namespace macisamuele {
namespace Resource {

struct ResourcePoolStats {
    size_t poolSize;
    size_t resourcesAcquired;
};

} /* namespace Resource */
} /* namespace macisamuele */

#endif /* RESOURCE_RESOURCEPOOLSTAT_H_ */
