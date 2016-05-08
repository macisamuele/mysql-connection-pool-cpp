#include <iostream>

#include "ConcreteMySqlPool.h"      // for ConcreteMySqlPool definition

int main() {
    macisamuele::MySQL::MySqlConfig aConfiguration("localhost", 3306, "root", "root");
    test::macisamuele::Resource::ConcreteMySqlPool aPool(2, aConfiguration);
    macisamuele::Resource::ResourceSP aResourceSP = aPool.acquire();
    macisamuele::Resource::ResourceInterfaceSP aResourceInterfaceSP = aResourceSP->getResourceInterface();
    aPool.release(aResourceSP);
    return 0;
}
