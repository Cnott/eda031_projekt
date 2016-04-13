/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** logger.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef LOGGER_H
#define LOGGER_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/
// not recommended -> using namespace std;

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/
class Logger {
public:
  Logger() {}
  ~Logger() {}

protected:
  unsigned int id;
  std::string author;
  std::string text;
private:

};

#endif