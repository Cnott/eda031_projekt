#include "memdatabase.h"

using namespace std;

bool MemDatabase::addNewsgroup(string ngName){
  Newsgroup ng(latestNewsgroupID,ngName);
  //checking if the name already exists
  for(auto it=newsgroupDB.begin();it!=newsgroupDB.end();it++){
    if(it->second.getName()==ngName){
      return false;
    }
  }
  if (newsgroupDB.insert(make_pair(latestNewsgroupID,ng)).second) {
    // Succesfully added ng to newsgroups.
    ++latestNewsgroupID;
    return true;
  } else {
    // Unsuccesfull at adding ngName to newsgroups.
    return false;
  }
}

bool MemDatabase::addArticle (unsigned int ngId, string title, string author, string text) {
  Article a1(latestArticleID, title, author, text);
  if (!newsgroupInDB(ngId))
   return false;
  if (newsgroupDB.at(ngId).add(a1)) {
    // Succesfully added a1 to articles in ngId.
    ++latestArticleID;
    return true;
  } else {
    // Unsuccesfull at adding a1 to articles in ngId.
    return false;
  }
}

bool MemDatabase::removeNewsgroup(unsigned int ngId) {
  if (!newsgroupInDB(ngId))
    return false;
  int success = newsgroupDB.erase(ngId);
  if (success > 0) {
    // Succesfully removed newsgroup.
    return true;
  }
  // Not succesfull in removing newsgroup.
  return false;
}

bool MemDatabase::removeArticle(unsigned int ngId, unsigned int aId){
  if (!newsgroupInDB(ngId))
    return false;
  int success = newsgroupDB.at(ngId).remove(aId);
  if (success > 0) {
    // Succesfully removed newsgroup.
    return true;
  }
  // Not succesfull in removing newsgroup.
  return false;
}

string MemDatabase::getNewsgroupName(unsigned int ngId) {
  if (!newsgroupInDB(ngId))
    return "";
  return newsgroupDB.at(ngId).getName();
}

vector<Newsgroup>  MemDatabase::listNewsgroups(){
  vector<Newsgroup> newsVector;
  for(auto it : newsgroupDB) { //iterate newsgroups
    newsVector.push_back(it.second);
  }
  return newsVector;
}

vector<Article>  MemDatabase::listArticles(unsigned int ngId){
  vector<Article> articleVector;
  for (auto it : newsgroupDB.at(ngId)) { //Iterate articles
    articleVector.push_back(it.second);
  }
  return articleVector;
}

const Article& MemDatabase::getArticle(unsigned int ngId, unsigned int artId){
  return newsgroupDB.at(ngId).at(artId);
}

bool MemDatabase::newsgroupInDB(unsigned int key) {
  if ( newsgroupDB.find(key) == newsgroupDB.end() ) {
  // not found
  return false;
  } else {
  // found
  return true;
  }
}

/*
    Returns true if article with key 'aKey', is in the db, specifically in the
    newsgroup with key 'ngKey'.

    Pre: Caller has already confirmed that newsgroup with ngKey is in the DB
*/
 // Possibly needs a bette solution.
bool MemDatabase::articleInDB(unsigned int ngKey, unsigned int aKey) {
  return newsgroupDB.at(ngKey).articleInNG(aKey);
}
