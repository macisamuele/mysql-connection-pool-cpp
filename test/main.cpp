#include <iostream>

#include "macisamuele/ConcreteMySqlPool.h"          // for ConcreteMySqlPool definition
#include "macisamuele/ConcreteMySqlConnection.h"    // for ConcreteMySqlConnection definition
#include "macisamuele/ConcreteMySqlInterface.h"     // for ConcreteMySqlInterface definition

using namespace std;
using namespace macisamuele;

int main() {
    MySQL::MySqlConfig aConfiguration("localhost", 3306, "root", "root", "information_schema");
    ConcreteMySqlPool aPool(2, aConfiguration);
    ConcreteMySqlConnectionSP aConnectionSP = aPool.acquireConnection();
    vector<string> aTablesList;
    aConnectionSP->getInterface()->getTables(aTablesList);
    aPool.release(aConnectionSP);
    cout << "Are available " << aTablesList.size() << " tables: " << endl;
    for(vector<string>::iterator it = aTablesList.begin(); it != aTablesList.end(); it++) {
    	cout << "    " << *it << endl;
    }
//    macisamuele::Resource::ResourceSP aResourceSP = aPool.acquire();
//    macisamuele::Resource::ResourceInterfaceSP aResourceInterfaceSP = aResourceSP->getResourceInterface();
//    macisamuele::Resource::ResourceSP aResourceSP = aPool.acquire();
//    macisamuele::Resource::ResourceInterfaceSP aRevector<string>sourceInterfaceSP = aResourceSP->getResourceInterface();

    return 0;
}
