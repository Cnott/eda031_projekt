#include "newsgroup.h"

using namespace std;
Newsgroup::Newsgroup(string name) {
  this->name = name;
}

string Newsgroup::getName() {
  return name;
}

unsigned int Newsgroup::getId() {
  return id;
}

bool Newsgroup::add(Article a) {
  if (articles.insert(make_pair(a.getId(),a)).second == false)
    return false;
  return true;
}

bool Newsgroup::remove(unsigned int id) {
  int success = articles.erase(id);
  if (success > 0)
    return true;
  return false;
}

const Article& Newsgroup::at(unsigned int id) {
  return articles.at(id);
}

map<unsigned int, Article>::iterator Newsgroup::begin() {
  return articles.begin();
}

map<unsigned int, Article>::iterator Newsgroup::end() {
  return articles.end();
}

bool Newsgroup::articleInNG(unsigned int key) {
  return articles.find(key) != articles.end();
}
