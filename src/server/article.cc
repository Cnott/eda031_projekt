#include "article.h"
#include <string>

using namespace std;

Article::Article(unsigned int id, string title, string author, string text) {
  this->title = title;
  this->author = author;
  this->text = text;
  this->id = id;
}

const unsigned int Article::getId() {
  return id;
}

const string Article::getTitle() {
  return title;
}

const string Article::getAuthor() {
  return author;
}

const string Article::getText() {
  return text;
}
