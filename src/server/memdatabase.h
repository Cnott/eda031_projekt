/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** memdatabase.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef MEMDATABASE_H
#define MEMDATABASE_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>

#include "database.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class MemDatabase : public Database {
public:
  MemDatabase();
  ~MemDatabase();

  void saveNewsgroup(std::string ngName);
  void saveArticle (int ngID, std::string artName, std::string author,
                            std::string text);
  void listNewsGroup();
  void listArticles(int nwId);
  void getArticle(int ngID, int artID);

private:

};

#endif
