/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** memdatabase.h
** Database that handles newsgroups and articles. Only keeps the objects in
** in memory and never saves to file.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef MEMDATABASE_H
#define MEMDATABASE_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>
#include <vector>
#include "newsgroup.h"

#include "database.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class MemDatabase : public Database {
public:
  MemDatabase() {
    latestNewsgroupID = 1;
    latestArticleID = 1;
  }
  ~MemDatabase() {};
  bool addNewsgroup(std::string ngName);
  bool addArticle (unsigned int ngId, std::string title, std::string author, std::string text);
  bool removeNewsgroup(unsigned int ngId);
  bool removeArticle(unsigned int ngId, unsigned int aId);
  std::string getNewsgroupName(unsigned int ngId);
  std::vector<Newsgroup> listNewsGroups();
  std::vector<Article> listArticles(unsigned int ngId);
  const Article& getArticle(unsigned int ngID, unsigned int artID);

  bool articleInDB(unsigned int ngKey, unsigned int aKey);  // Possibly needs a bette solution.

private:
  bool newsgroupInDB(unsigned int);
  std::map<unsigned int, Newsgroup> newsgroupDB;
  unsigned int latestNewsgroupID;
  unsigned int latestArticleID;

};

#endif
