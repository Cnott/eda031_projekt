/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** database.h
**
** An interface for a newsgroup database. Functions to create and delete
** newsgroups and articles.
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
    C L A S S   D E F
-------------------------------------*/

class Database {
public:
  virtual ~Database() {}

  virtual bool addNewsgroup       ( std::string ngName                    ) = 0;
  virtual bool addArticle         ( unsigned int ngId, std::string artName,
                                    std::string author, std::string text  ) = 0;
  virtual bool removeNewsgroup    ( unsigned int ngId                     ) = 0;
  virtual bool removeArticle      ( unsigned int ngId, unsigned int aId   ) = 0;
  virtual bool articleInDB        ( unsigned int ngKey, unsigned int aKey ) = 0;
  virtual bool newsgroupInDB      ( unsigned int                          ) = 0;

  virtual const Article&          getArticle      ( unsigned int ngID,
                                                    unsigned int artID    ) = 0;
  virtual std::vector<Newsgroup>  listNewsgroups  (                       ) = 0;
  virtual std::vector<Article>    listArticles    ( unsigned int ngId     ) = 0;

private:
};

#endif  // DATABASE_H
