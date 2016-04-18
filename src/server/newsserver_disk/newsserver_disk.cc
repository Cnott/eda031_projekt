/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** newsserver_disk.cc
**
** Runs a newsserver with a static DiskDatabase.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/

#include "../newsserver.h"
#include "diskdatabase.h"

using namespace std;
int main(int argc, char* argv[]) {
  DiskDatabase db;
  NewsServer ns(argc, argv);
  
  try {
    ns.run(db);
  } catch (exception& e) {
    cout << " Error: Something went wrong. Server is closing." << endl;
    exit(1);
  }
}
