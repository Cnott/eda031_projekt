#include "newsserver.h"
#include "database.h"
#include "memdatabase.h"

int main(int argc, char* argv[]) {
  MemDatabase db;
  NewsServer ns(argc, argv);
  ns.run(db);
}
