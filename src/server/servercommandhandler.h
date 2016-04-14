/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** servercommandhandler.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef SERVERCOMMANDHANDLER_H
#define SERVERCOMMANDHANDLER_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include "../common/messagehandler.h"
#include "../common/protocol.h"
#include "database.h"
#include "newsgroup.h"

#include <vector>

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class ServerCommandHandler {
public:
  ServerCommandHandler(MessageHandler&, Database&);
  void update();


private:
  void listNewsgroups();

  MessageHandler msH;
  Database* db;
};

#endif
