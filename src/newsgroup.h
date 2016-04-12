/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** newsgroup.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef NEWSGROUP_H
#define NEWSGROUP_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/
using namespace std;

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class Newsgroup() {
public:
  Newsgroup() {}
  ~Newsgroup() {}

protected:
  string name;
  uint id;
private:

};

#endif
