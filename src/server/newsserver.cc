#include "newsserver.h"

NewsServer::NewsServer(int argc, char* argv[]) {
  if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
}

NewsServer::~NewsServer() {}

void NewsServer::run() {
  server = Server(port);
  if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

  while (true) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
      try {
        int nbr = readNumber(conn);
        string result;
        if (nbr > 0) {
          result = "positive";
        } else if (nbr == 0) {
          result = "zero";
        } else {
          result = "negative";
        }
        writeString(conn, result);
      } catch (ConnectionClosedException&) {
        server.deregisterConnection(conn);
        cout << "Client closed connection" << endl;
      }
    } else {
      conn = make_shared<Connection>();
      server.registerConnection(conn);
      cout << "New client connects" << endl;
    }
  }
}
