#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <list>
#include <forward_list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <regex>
#include <random>
#include <stdexcept>
#include "../server/article.h"
#include "../common/constants.h"
#include "../server/newsgroup.h"
#include "../common/messagehandler.h"

using namespace std;

int main() {
  cout << "This is a tester to check functionality of our classes: ";
  cout << endl;
  string aText = "This article is about elephants.";
  string aAuthor = "Anton Friberg";
  string aTitle = "National Neographics: Elephants";
  unsigned int id = 1;
  Article a1(id, aTitle, aAuthor, aText);
  cout << a1.getId() << "\n";
  cout << a1.getTitle() << "\n";
  cout << a1.getAuthor() << "\n";
  cout << a1.getText() << endl;
  return 0;
}
