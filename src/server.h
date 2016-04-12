/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** server.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef _server_h
#define _server_h

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>
#include "connection.h"

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

/* A server listens to a port and handles multiple connections */
class Server() {
public:
  /*  Creates a server that listens to a port */
  explicit Server(int port);

  /*  Removes all registered connections */
  virtual ~Server();

  /*  Returns true is the server has been initialized correctly */
  bool isReady() const;

  /*  Waits for activity on the port. Returns a previously registered
      connection object if an existing client wishes to communicate,
      nullptr if a new client wishes to communicate */
  std::shared_ptr<Connection> waitForActivity() const;

  /*  Registers a new connection */
  void registerConnection(const std::shared_ptr<Connection>& conn);

  /*  Deregisters a connection */
  void deregisterConnection(const std::shared_ptr<Connection>& conn);

  /* Forbid copying of Server objects */
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;
};

#endif
