#include "memdatabase.h"

MemDatabase::MemDatabase(){ }
MemDatabase::~MemDatabase(){ }

void MemDatabase::saveNewsgroup(std::string ngName){ }
void MemDatabase::saveArticle (int ngID, std::string artName, std::string author,
                          std::string text){ }
void MemDatabase::listNewsGroup(){ }
void MemDatabase::listArticles(int nwId){ }
void MemDatabase::getArticle(int ngID, int artID){ }
