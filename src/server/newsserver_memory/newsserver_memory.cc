#include "../newsserver.h"
//#include "../database.h"
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
