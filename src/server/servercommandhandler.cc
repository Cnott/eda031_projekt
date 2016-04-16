#include "servercommandhandler.h"
#include <iostream>

using namespace std;

ServerCommandHandler::ServerCommandHandler(MessageHandler& msH, Database& db)
  : msH(msH) {
    this->db = &db;
  }

void ServerCommandHandler::update() {
  int cmd = msH.recvCode();
  switch (cmd) {
    case Protocol::COM_LIST_NG:     // list newsgroups
      listNewsgroups();
      break;
    case Protocol::COM_CREATE_NG:   // create newsgroup
      createNewsgroup();
      break;
    case Protocol::COM_DELETE_NG:   // delete newsgroup
      deleteNewsgroup();
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
/*
    COM_LIST_NG COM_END
    ANS_LIST_NG num_p [num_p string_p]* ANS_END
*/
void ServerCommandHandler::listNewsgroups() {
  msH.sendCode(Protocol::ANS_LIST_NG);                // ANS_LIST_NG
  vector<Newsgroup> groups = db->listNewsgroups();

  msH.sendIntParameter(groups.size());                // num_p
  for (auto ng : groups) {
    msH.sendIntParameter(ng.getId());                 // [num_p
    msH.sendStringParameter(ng.getName());            // string_p]
  }
  msH.sendCode(Protocol::ANS_END);                    // ANS_END
}

/*
    COM_CREATE_NG string_p COM_END
    ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
*/
// Error: still able to create two newsgroups with the same name
void ServerCommandHandler::createNewsgroup(){
    string groupName = msH.recvStringParameter();     // string_p

    msH.sendCode(Protocol::ANS_CREATE_NG);            // ANS_CREATE_NG
    if (db->addNewsgroup(groupName)) {
      msH.sendCode(Protocol::ANS_ACK);                // ANS_ACK
    } else {
      msH.sendCode(Protocol::ANS_NAK);                // ANS_NAK
      msH.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);  // ERR_NG_ALREADY_EXISTS
    }
    msH.sendCode(Protocol::ANS_END);                  // ANS_END
}
/*
    COM_DELETE_NG num_p COM_END
    ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
*/
void ServerCommandHandler::deleteNewsgroup() {
    int groupId = msH.recvIntParameter();             // num_p

    msH.sendCode(Protocol::ANS_DELETE_NG);             // ANS_DELETE_NG
    if (db->removeNewsgroup(groupId)) {
      msH.sendCode(Protocol::ANS_ACK);                // ANS_ACK
    } else {
      msH.sendCode(Protocol::ANS_NAK);                // ANS_NAK
      msH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);  // ERR_NG_DOES_NOT_EXIST
    }
    msH.sendCode(Protocol::ANS_END);                  // ANS_END
}

/*
    COM_LIST_ART num_p COM_END
    ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* |
    ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
*/
void ServerCommandHandler::listArticles() {
  unsigned int groupId = msH.recvIntParameter();      // num_p
  msH.sendCode(Protocol::ANS_LIST_ART);
  if (db->newsgroupInDB(groupId)) {
                 // ANS_LIST_ART
    msH.sendCode(Protocol::ANS_ACK);                  // ANS_ACK

    vector<Article> articles = db->listArticles(groupId);
    msH.sendIntParameter(articles.size());            // num_p
    for (auto a : articles) {
      msH.sendIntParameter(a.getId());                // [num_p
      msH.sendStringParameter(a.getTitle());          // string_p]
    }
  } else {
      msH.sendCode(Protocol::ANS_NAK);                // ANS_NAK
      msH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);  // ERR_NG_DOES_NOT_EXIST
  }
  msH.sendCode(Protocol::ANS_END);                    // ANS_END
}

/*
    COM_CREATE_ART num_p string_p string_p string_p COM_END
    ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
*/
void ServerCommandHandler::createArticle() {
  unsigned int groupId = msH.recvIntParameter();      // num_p
  string title = msH.recvStringParameter();           // string_p
  string author = msH.recvStringParameter();          // string_p
  string text = msH.recvStringParameter();            // string_p

  msH.sendCode(Protocol::ANS_CREATE_ART);             // ANS_CREATE_ART
  if (db->addArticle(groupId, title, author, text)) {
    msH.sendCode(Protocol::ANS_ACK);                  // ANS_ACK
  } else {
    msH.sendCode(Protocol::ANS_NAK);                  // ANS_NAK
    msH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);    // ERR_NG_DOES_NOT_EXIST
  }
  msH.sendCode(Protocol::ANS_END);                    // ANS_END
}

/*
    COM_DELETE_ART num_p num_p COM_END
    ANS_DELETE_ART [ANS_ACK |
    ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
*/
void ServerCommandHandler::deleteArticle() {
  unsigned int groupId = msH.recvIntParameter();      // num_p
  unsigned int articleId = msH.recvIntParameter();    // num_p

  msH.sendCode(Protocol::ANS_DELETE_ART);             // ANS_DELETE_ART
  if (db->removeArticle(groupId, articleId)) {
    msH.sendCode(Protocol::ANS_ACK);                  // ANS_ACK
  } else {
    msH.sendCode(Protocol::ANS_NAK);                  // ANS_NAK
    if (!db->newsgroupInDB(groupId)) {
      msH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);  // [ ERR_NG_DOES_NOT_EXIST
    } else {
    msH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);   // ERR_ART_DOES_NOT_EXIST]
    }
  }
  msH.sendCode(Protocol::ANS_END);                    // ANS_END
}

/*
    COM_GET_ART num_p num_p COM_END
    ANS_GET_ART [ANS_ACK string_p string_p string_p |
    ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
*/
void ServerCommandHandler::getArticle() {
  unsigned int groupId = msH.recvIntParameter();      // num_p
  unsigned int articleId = msH.recvIntParameter();    // num_p

  msH.sendCode(Protocol::ANS_GET_ART);                // ANS_GET_ART
  if (db->newsgroupInDB(groupId)) {
    if (db->articleInDB(groupId, articleId)) {
      msH.sendCode(Protocol::ANS_ACK);                // [ANS_ACK
      Article a = db->getArticle(groupId, articleId);
      msH.sendStringParameter(a.getTitle());          // string_p
      msH.sendStringParameter(a.getAuthor());         // string_p
      msH.sendStringParameter(a.getText());           // string_p]
    } else {
        msH.sendCode(Protocol::ANS_NAK);              // ANS_NAK
        msH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);// ERR_ART_DOES_NOT_EXIST
    }
  } else {
      msH.sendCode(Protocol::ANS_NAK);                // ANS_NAK
      msH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST); // ERR_NG_DOES_NOT_EXIST
  }
  msH.sendCode(Protocol::ANS_END);                    // ANS_END
}
