#include "servercommandhandler.h"

ServerCommandHandler::ServerCommandHandler(MessageHandler& msH, Database& db)
  : msH(msH), db(db) {}

void ServerCommandHandler::update() {
  int cmd = msH.recvCode();

  switch (cmd) {
    case Protocol::COM_LIST_NG:     // list newsgroups

    msH.sendCode(Protocol::ANS_END);
    break;
    case Protocol::COM_CREATE_NG:   // create newsgroup

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
