#include "newsserver.h"

using namespace std;

NewsServer::NewsServer(int argc, char* argv[]) {
  if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}

	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
  cout << "\nport: " << port << endl;
}

NewsServer::~NewsServer() {}

void NewsServer::run(Database& db_in) {
  // init db pointer and start Server object
  Database* db = &db_in;
  Server server(port);

  // check if everything is going as excpected
  if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

  // main run loop
  while (true) {
    auto conn = server.waitForActivity();

    // while we have a connection
    if (conn != nullptr) {
      // handle messages to the server
      try {
        MessageHandler msH(*conn.get());
        ServerCommandHandler scH(msH, *db);
        scH.execute();
      } catch (ConnectionClosedException e) {
        server.deregisterConnection(conn);
        cout<<"Client closed the connection"<<endl;
      }
    } else {
      conn = make_shared<Connection>();
      server.registerConnection(conn);
      cout << "New client connects" << endl;
    }
  }
}
