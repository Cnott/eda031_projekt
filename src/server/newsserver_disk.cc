#include "newsserver.h"
#include "database.h"
#include "diskdatabase.h"

int main(int argc, char* argv[]) {
  DiskDatabase db;
  NewsServer ns(argc, argv);
  ns.run(db);
}
