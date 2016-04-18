#include "../newsserver.h"
//#include "../database.h"
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
