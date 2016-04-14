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
#include "../common/connection.h"
#include "../common/connectionclosedexception.h"
#include "../common/messagehandler.h"
#include "database.h"
#include "servercommandhandler.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class NewsServer {
public:
  NewsServer(int argc, char* argv[]);
  ~NewsServer();
  void run(Database& db);

private:
  int port = -1;
};

#endif
