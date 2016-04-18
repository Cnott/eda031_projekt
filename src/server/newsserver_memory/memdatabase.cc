#include "memdatabase.h"

using namespace std;

/*  Adds a newsgroup to the database if it does not already exist. */
bool MemDatabase::addNewsgroup(string ngName){
  Newsgroup ng(latestNewsgroupID,ngName);
  //checking if the name already exists
  for(auto it = newsgroupDB.begin(); it!=newsgroupDB.end(); it++) {
    if(it->second.getName() == ngName){
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

/* Adds article aId to newsgroup ngId if the newsgroup exists. */
bool MemDatabase::addArticle (unsigned int ngId, string title,
                              string author, string text) {
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

/* Removes the newsgroup with id ngId and returns true if sucessful. */
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

/*  Tries to remove the article aId from the database and returns true if
    successful. If either article or newsgroup do not exist, returns false.
*/
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

/*  Returns the name of the newsgroup with id ngId, if it exists.*/
string MemDatabase::getNewsgroupName(unsigned int ngId) {
  if (!newsgroupInDB(ngId))
    return "";
  return newsgroupDB.at(ngId).getName();
}

/*  Returns a vector with all newsgroups in the database, sorted in order of
    their ngId - which are given in chronological (creation) order.
*/
vector<Newsgroup>  MemDatabase::listNewsgroups(){
  vector<Newsgroup> newsVector;
  for(auto it : newsgroupDB) { //iterate newsgroups
    newsVector.push_back(it.second);
  }
  return newsVector;
}

/*  Returns a vector of all the articles in the newsgroup ngId in order of
    their aId.
*/
vector<Article>  MemDatabase::listArticles(unsigned int ngId){
  vector<Article> articleVector;
  for (auto it : newsgroupDB.at(ngId)) { //Iterate articles
    articleVector.push_back(it.second);
  }
  return articleVector;
}

/*  Returns the article with id aId in the newsgroup ngId, if both exist.
    @pre: Caller should make sure the article exists
*/
const Article& MemDatabase::getArticle(unsigned int ngId, unsigned int artId){
  return newsgroupDB.at(ngId).at(artId);
}

/*  Returns true if the newsgroup ngId is already in the database. False
    otherwise.
*/
bool MemDatabase::newsgroupInDB(unsigned int key) {
  return  !(newsgroupDB.find(key) == newsgroupDB.end());
}

/*  Returns true if article with key 'aKey', is in the db, specifically in the
    newsgroup with key 'ngKey'.
    @pre: Caller has already confirmed that newsgroup with ngKey is in the DB
*/
bool MemDatabase::articleInDB(unsigned int ngKey, unsigned int aKey) {
  return newsgroupDB.at(ngKey).articleInNG(aKey);
}
