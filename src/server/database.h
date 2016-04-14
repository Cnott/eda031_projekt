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

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class Database {
public:
  virtual ~Database() {}

  virtual void saveNewsgroup(std::string ngName) {};
  virtual void saveArticle (int ngID, std::string artName, std::string author,
                            std::string text) {};
  virtual void listNewsGroup() {};
  virtual void listArticles(int nwId) {};
  virtual void getArticle(int ngID, int artID) {};

private:

};

#endif
