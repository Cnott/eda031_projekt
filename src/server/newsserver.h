/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** newsserver.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef NEWSSERVER_H
#define NEWSSERVER_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <iostream>
#include <string>
#include <stdexcept>

#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "../common/MessageHandler.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class NewsServer {
public:
  NewsServer() {}
  ~NewsServer() {}
  void run();

private:
  int port = -1;
  Server server;
  MessageHandler msgH;

};

#endif
