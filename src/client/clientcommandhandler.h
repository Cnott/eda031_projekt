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
#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H

#include <utility>
#include <vector>
#include <string>
#include "../common/protocol.h"

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include "../common/messagehandler.h"
#include "../common/protocol.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class ClientCommandHandler {
public:
  ClientCommandHandler(MessageHandler& mh): msH(mh) {}
  std::string update(std::pair<int,std::vector<std::string>>&);

private:
  void listNewsgroups();
  void createNewsGroup();
  void deleteNewsGroup();
  void listArticles();
  void createArticle();
  void deleteArticle();
  void getArticle();

  MessageHandler msH;
};

#endif