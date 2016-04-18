/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** memdatabase.h
**
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

#include "../newsgroup.h"
#include "../database.h"

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class MemDatabase : public Database {
public:
  MemDatabase() {
    latestNewsgroupID = 1;
  }
  ~MemDatabase() {};
  bool addNewsgroup                       ( std::string ngName      );
  bool addArticle                         ( unsigned int ngId,
                                            std::string title,
                                            std::string author,
                                            std::string text        );
  bool removeArticle                      ( unsigned int ngId,
                                            unsigned int aId        );
  bool removeNewsgroup                    ( unsigned int ngId       );


  std::vector<Newsgroup>  listNewsgroups  ();
  std::vector<Article>    listArticles    ( unsigned int ngId       );
  const Article&          getArticle      ( unsigned int ngID,
                                            unsigned int artID      );

private:
  bool        newsgroupInDB               ( unsigned int            );
  bool        articleInDB                 ( unsigned int ngKey,
                                            unsigned int aKey       );

  std::string getNewsgroupName            ( unsigned int ngId       );

  unsigned int latestNewsgroupID;
  std::map<unsigned int, Newsgroup> newsgroupDB;

};

#endif  // MEMDATABASE_H
