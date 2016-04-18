/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** messagehandler.h
** Handles "low protocol level" communication. Used both by server and client.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>
#include "connection.h"
#include "exceptions/connectionclosedexception.h"
#include "protocol.h"

/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

class MessageHandler {
public:
  MessageHandler  (Connection &c );
  ~MessageHandler ();

  void sendCode                     ( int code          );
  void sendInt                      ( int value         );
  void sendIntParameter             ( int param         );
  void sendStringParameter          ( std::string param );

  int recvCode                      ();
  int recvInt                       ();
  int recvIntParameter              ();
  std::string recvStringParameter   ();

protected:

private:
  Connection *conn;                 // the connection
  void  sendByte                    ( int i             );
  int   recvByte                    ();
};

#endif // MESSAGEHANDLER_H
