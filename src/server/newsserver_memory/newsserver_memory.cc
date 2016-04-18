/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** newsserver_memory.cc
**
** Runs a newsserver with a cached MemDatabase.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#include "../newsserver.h"
#include "memdatabase.h"
#include <exception>

using namespace std;
int main(int argc, char* argv[]) {
  MemDatabase db;
  NewsServer ns(argc, argv);

  try {
    ns.run(db);
  } catch (exception& e) {
    cout << " Error: Something went wrong. Server is closing." << endl;
    exit(1);
  }
}
