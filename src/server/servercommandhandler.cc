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
      createNewsGroup();
      break;
    case Protocol::COM_DELETE_NG:   // delete newsgroup

      break;
    case Protocol::COM_LIST_ART:    // list articles

      break;
    case Protocol::COM_CREATE_ART:  // create article

      break;
    case Protocol::COM_DELETE_ART:  // delete article

      break;
    case Protocol::COM_GET_ART:     // get article

      break;
    case Protocol::COM_END:         // command end

      break;
  }

}

void ServerCommandHandler::listNewsgroups() {
  msH.sendCode(Protocol::ANS_LIST_NG);
  vector<Newsgroup> groups = db->listNewsGroups();

  msH.sendIntParameter(groups.size());
  for (auto ng : groups) {
    msH.sendIntParameter(ng.getId());
    msH.sendStringParameter(ng.getName());
  }
  msH.sendCode(Protocol::ANS_END);
}

void ServerCommandHandler::createNewsGroup(){
    string groupName = msH.recvStringParameter();


    msH.sendCode(Protocol::ANS_CREATE_NG);
    if (db->addNewsgroup(groupName)) {
      msH.sendCode(Protocol::ANS_ACK);
    } else {
      msH.sendCode(Protocol::ANS_NAK);
      msH.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
    }
    msH.sendCode(Protocol::ANS_END);
}
