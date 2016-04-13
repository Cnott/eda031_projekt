#include "newsserver.h"

int main(int argc, char* argv[]) {  
  NewsServer ns = NewsServer(argc, argv);
  ns.run();
}
