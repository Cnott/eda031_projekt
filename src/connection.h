/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** connection.h
** <very brief file description>
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef _connection_h
#define _connection_h

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <string>

/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/

/* A ConnectionClosedException is thrown when a connection is closed */
struct ConnectionClosedException {};

/* A Connection object represents a socket */
class Connection() {
public:
  /*  Establishes a connection to the computer 'host' via
      the port 'port' */
  Connection(const char* host, int port);

  /*  Creates a Connection object which will be initialized
      by the server */
  Connection();

  /*  Closes the connection */
  virtual ~Connection();

  /*  Returns true if the connection has been established */
  bool isConnected() const;

  /* Writes a character (throws ConnectionClosedException) */
  void write(unsigned char ch) const;

  /* Reads a character (throws ConnectionClosedException) */
  unsigned char read() const;

  /* Forbid copying of connection objects */
  Connection(const Connection&) = delete;
  Connection& operator=(const Connection&) = delete;
};

#endif
