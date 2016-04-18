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


/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <exception>

#include "../connection/protocol.h"
#include "../connection/messagehandler.h"
#include "../connection/exceptions/ngexistsexception.h"
#include "../connection/exceptions/ngdoesnotexistexception.h"
#include "../connection/exceptions/noarticleexception.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class ClientCommandHandler {
public:
  ClientCommandHandler(MessageHandler& mh): msH(mh) {}
  std::string execute(std::pair<int,std::vector<std::string> >);

private:
  std::string listNewsgroups();
  std::string createNewsGroup(std::vector<std::string> &) throw (NGExistsException);
  std::string deleteNewsGroup(std::vector<std::string> &) throw (NGDoesNotExistException);
  std::string listArticles(std::vector<std::string> &) throw (NGDoesNotExistException);
  std::string createArticle(std::vector<std::string> &) throw (NGDoesNotExistException);
  std::string deleteArticle(std::vector<std::string> &) throw (NGDoesNotExistException, ArticleDoesNotExistException);
  std::string getArticle(std::vector<std::string> &) throw (NGDoesNotExistException, ArticleDoesNotExistException);

  MessageHandler msH;
};

#endif
