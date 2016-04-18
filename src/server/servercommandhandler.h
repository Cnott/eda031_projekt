/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** servercommandhandler.h
** Handles input to the server and responds accordingly. All input comes
** through the MessageHandler and is assumed to follow the Protocol.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef SERVERCOMMANDHANDLER_H
#define SERVERCOMMANDHANDLER_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include "../connection/messagehandler.h"
#include "../connection/protocol.h"
#include "database.h"
#include "newsgroup.h"

#include <vector>

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class ServerCommandHandler {
public:
  ServerCommandHandler    ( MessageHandler&, Database&  );
  void execute            ();
private:
  void listNewsgroups     ();
  void createNewsgroup    ();
  void deleteNewsgroup    ();
  void listArticles       ();
  void createArticle      ();
  void deleteArticle      ();
  void getArticle         ();

  MessageHandler msH;
  Database* db;
};

#endif
