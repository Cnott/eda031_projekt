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
#include <map>
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
  cout << a1.getText() << "\n" << endl;

  Article a2(2, "National Neographics: Giraffe", "Lasse Åberg", "This article is about giraffes.");
  Article a3(3, "National Neographics: Hippopotumus", "Scott Manley", "This article is about hippopotumuses.");
  Article a4(4, "National Neographics: Lion", "Mr Smith", "This article is about lions.");



  Newsgroup nn ("Nature News");
  nn.add(a1); nn.add(a2); nn.add(a3); nn.add(a4);
  for (auto it : nn) {
    cout << "Author: " << it.second.getAuthor() << endl;
    cout << "Title: " << it.second.getTitle() << endl;
    cout << "Text: " << it.second.getText() << endl;
    cout << "\n" << endl;
  }

  return 0;
}
