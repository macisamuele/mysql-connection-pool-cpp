#include <iostream>

#include "ConcreteMySqlPool.h"      // for ConcreteMySqlPool definition

int main() {
    macisamuele::MySQL::MySqlConfig aConfiguration;
    std::cout << "AAA" << std::endl;
    test::macisamuele::resource::ConcreteMySqlPool aPool(10, aConfiguration);
    std::cout << "AAA" << std::endl;
    return 0;
}
