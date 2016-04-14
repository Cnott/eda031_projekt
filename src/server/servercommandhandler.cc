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

      msH.sendCode(Protocol::ANS_END);
    break;
    case Protocol::COM_CREATE_NG:   // create newsgroup
    createNewsGroup();
    msH.sendCode(Protocol::ANS_END);
    break;
    case Protocol::COM_DELETE_NG:   // delete newsgroup

    msH.sendCode(Protocol::ANS_END);

    break;
    case Protocol::COM_LIST_ART:    // list articles

    msH.sendCode(Protocol::ANS_END);

    break;
    case Protocol::COM_CREATE_ART:  // create article

    msH.sendCode(Protocol::ANS_END);

    break;
    case Protocol::COM_DELETE_ART:  // delete article

    msH.sendCode(Protocol::ANS_END);

    break;
    case Protocol::COM_GET_ART:     // get article

    msH.sendCode(Protocol::ANS_END);

    break;
    case Protocol::COM_END:         // command end

    msH.sendCode(Protocol::ANS_END);

    break;
  }
}

void ServerCommandHandler::listNewsgroups() {
  msH.sendCode(Protocol::ANS_LIST_NG);
  vector<Newsgroup> ngs = db->listNewsGroups();

  msH.sendIntParameter(ngs.size());
  msH.sendCode(Protocol::ANS_LIST_NG);
}

void ServerCommandHandler::createNewsGroup(){
    cout<<"Hello im here"<<endl;
}
