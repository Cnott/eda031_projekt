#include "clientcommandhandler.h"

using namespace std;


string ClientCommandHandler::update(pair<int,vector<string>> &op){
  int cmd = op.first;
  switch (cmd) {
    case Protocol::COM_LIST_NG:     // list newsgroups
      listNewsgroups();
      break;
    case Protocol::COM_CREATE_NG:   // create newsgroup
      createNewsGroup();
      break;
    case Protocol::COM_DELETE_NG:   // delete newsgroup
      deleteNewsGroup();
      break;
    case Protocol::COM_LIST_ART:    // list articles
      listArticles();
      break;
    case Protocol::COM_CREATE_ART:  // create article
      createArticle();
      break;
    case Protocol::COM_DELETE_ART:  // delete article
      deleteArticle();
      break;
    case Protocol::COM_GET_ART:     // get article
      getArticle();
      break;
    case Protocol::COM_END:         // command end
      // not really needed atm, but keeping "in case shit"
      break;
  }


}

void ClientCommandHandler::listNewsgroups(){

}
void ClientCommandHandler::createNewsGroup(){

}
void ClientCommandHandler::deleteNewsGroup(){

}
void ClientCommandHandler::listArticles(){

}
void ClientCommandHandler::createArticle(){

}
void ClientCommandHandler::deleteArticle(){

}
void ClientCommandHandler::getArticle(){

}
