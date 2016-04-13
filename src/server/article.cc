#include "article.h"
#include <string>

using namespace std;

Article::Article(unsigned int id, string title, string author, string text) {
  this->title = title;
  this->author = author;
  this->text = text;
  this->id = id;
}
const string Article::getText() {
  return text;
}
