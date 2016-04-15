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
  Database* db = &db_in;
  Server server(port);

  if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

  while (true) {

    auto conn = server.waitForActivity();

    if (conn != nullptr) {
      // handle messages
      MessageHandler msH(*conn.get());
      ServerCommandHandler scH(msH, *db);

      try {
        scH.update();
      } catch (ConnectionClosedException e) {

      }
    } else {
      conn = make_shared<Connection>();
      server.registerConnection(conn);
      cout << "New client connects" << endl;
    }
  }
}
