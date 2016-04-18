/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** newsserver.h
** Runs a Server and connects it to a Database using a ServerCommandHandler,
** and a MessageHandler.
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
#include "database.h"
#include "servercommandhandler.h"
#include "../connection/connection.h"
#include "../connection/exceptions/connectionclosedexception.h"
#include "../connection/messagehandler.h"

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class NewsServer {
public:
  NewsServer    ( int argc, char* argv[]  );
  ~NewsServer   ();

  void run      ( Database& db            );
private:
  int port = -1;
};

#endif  // NEWSSERVER_H
