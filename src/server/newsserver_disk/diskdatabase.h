/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** diskdatabase.h
** Database that handles newsgroups and articles. Only keeps the objects in
** in memory and never saves to file.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef DISKDATABASE_H
#define DISKDATABASE_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>
#include <vector>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <sys/stat.h>
#include <unistd.h>

#include "../newsgroup.h"
#include "../database.h"

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class DiskDatabase : public Database {
public:
  DiskDatabase          ();
  ~DiskDatabase         () { closedir(dbRootDir); }

  bool addArticle       ( unsigned int ngId,  std::string title,
                          std::string author, std::string text      );
  bool addNewsgroup     ( std::string ngName                        );
  bool articleInDB      ( unsigned int ngKey, unsigned int aKey     );
  bool newsgroupInDB    ( unsigned int ngId                         );
  bool newsgroupInDB    ( std::string                               );
  bool removeNewsgroup  ( unsigned int ngId                         );
  bool removeArticle    ( unsigned int ngId,  unsigned int aId      );

  const Article&          getArticle        ( unsigned int ngID,
                                              unsigned int artID    );
  std::string             getNewsgroupName  ( unsigned int ngId     );
  std::vector<Newsgroup>  listNewsgroups    (                       );
  std::vector<Article>    listArticles      ( unsigned int ngId     );

private:
  void print                    ();
  void initDatabase             ();
  void saveDBInfo               ();
  void saveNGInfo               ( std::string name,
                                  unsigned int ngId,
                                  unsigned int aId                  );

  unsigned int latestArticleId  ( unsigned int ngId                 );
  std::string path              ( unsigned int ngId                 );
  std::string path              ( unsigned int ngId,
                                  unsigned int aId                  );

  std::map<unsigned int, Newsgroup>   newsgroupDB;
  unsigned int                        latestNewsgroupID;
  Article                             tmpArticle;

  std::string dbRoot        = "database/";
  unsigned char isDir       = 0x4;
  DIR* dbRootDir;
};

#endif  // DISKDATABASE_H
