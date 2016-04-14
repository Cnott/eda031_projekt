/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** database.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef DATABASE_H
#define DATABASE_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>
#include <vector>
#include "newsgroup.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class Database {
public:
  virtual ~Database() {}
  virtual bool addNewsgroup(std::string ngName) = 0;
  virtual bool addArticle(unsigned int ngId, std::string artName, std::string author, std::string text) = 0;
  virtual bool removeNewsgroup(unsigned int ngId) = 0;
  virtual bool removeArticle(unsigned int ngId, unsigned int aId) = 0;
  virtual std::string getNewsgroupName(unsigned int ngId) = 0;
  virtual std::vector<Newsgroup> listNewsGroups() = 0;
  virtual std::vector<Article> listArticles(unsigned int ngId) = 0;
  virtual const Article& getArticle(unsigned int ngID, unsigned int artID) = 0;
private:
  virtual bool newsgroupInDB(unsigned int) = 0;
};

#endif
