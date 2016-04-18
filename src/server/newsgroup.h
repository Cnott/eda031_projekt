/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** newsgroup.h
** A container class for articles.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef NEWSGROUP_H
#define NEWSGROUP_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>
#include <map>
#include "article.h"

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class Newsgroup {
public:
  Newsgroup(unsigned int, std::string name);

  bool add                    ( Article            );
  bool remove                 ( unsigned int       );
  bool articleInNG            ( unsigned int key   );
  const Article& at           ( unsigned int       );
  std::string getName         ();
  unsigned int getId          ();

  std::map<unsigned int, Article>::iterator begin ();
  std::map<unsigned int, Article>::iterator end   ();

private:
  std::string   name;
  unsigned int  id;
  std::map<unsigned int, Article> articles;

};

#endif // NEWSGROUP_H
