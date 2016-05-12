#include <iostream>

#include "macisamuele/ConcreteMySqlPool.h"          // for ConcreteMySqlPool definition
#include "macisamuele/ConcreteMySqlConnection.h"    // for ConcreteMySqlConnection definition

using namespace std;
using namespace macisamuele;

int main() {
    MySQL::MySqlConfig aConfiguration("localhost", 3306, "root", "root", "information_schema");
    ConcreteMySqlPool aPool(2, aConfiguration);
    ConcreteMySqlConnectionSP aConnectionSP = aPool.acquireConnection();
    vector<string> aTablesList;
    aConnectionSP->getTables(aTablesList);
    aPool.release(aConnectionSP);
    cout << "Are available " << aTablesList.size() << " tables: " << endl;
    for (vector<string>::iterator it = aTablesList.begin(); it != aTablesList.end(); it++) {
        cout << "    " << *it << endl;
    }
    return 0;
}
