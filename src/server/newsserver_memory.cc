#include "newsserver.h"

int main(int argc, char* argv[]) {
  NewsServer ns(argc, argv);
  ns.run();
}
