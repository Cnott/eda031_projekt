#include "clientMain.h"

using namespace std;
namespace {
  string info     = "This is a newsgroup client. Type 'help' for a list of "
                    "commands, 'q' to quit.";
  string listN    = "list:\t\t\t Lists newsgroups on server.";
  string listA    = "list x:\t\t\t Lists articles on newsgroup number x.";
  string getA     = "get x y:\t\t Retrieves article y from newsgroup x.";
  string createN  = "create newsgroup x:\t Creates new newsgroup with name x.";
  string createA  = "create article x path:\t Creates new article in "
                    "newsgroup x from the content\n\t\t\t of the file "
                    "specified. The file should have title\n\t\t\t on the "
                    "first row followed by the author on the\n\t\t\t "
                    "second and the text content on the remaining.";
  string deleteN  = "delete newsgroup x:\t Deletes newsgroup x.";
  string deleteA  = "delete article x y:\t Deletes article y from newsgroup x.";

  vector<string> helpInfo = { listN, listA, getA, createN,
                              createA, deleteN, deleteA     };
}

int main(int argc, char* argv[]) {

  if (argc != 3) {
		cerr << "Usage: client host-name port-number" << endl;
		exit(1);
	}

  int port = -1;
  try {
    port = stoi(argv[2]);
  } catch (exception& e) {
    cerr << "Wrong port number. " << e.what() << endl;
    exit(1);
  }

  Connection conn(argv[1], port);
  if (!conn.isConnected()) {
    cerr << "Connection attempt failed" << endl;
    exit(1);
  }

  // Communication handlers
  MessageHandler msH(conn);
  ClientCommandHandler ccH(msH);
  InputHandler ih;

  // Main loop
  cout << string(80, '-')  << endl << info << endl << string(80, '-') << endl;
	while (true) {
    cout << "Enter a command: ";
		try {
      string input;
      string output;
			getline(cin, input);

      // take care of input
      if (input == "help") {
        for(auto it : helpInfo) {
          cout << it << endl;
      }
        cout << string(80, '-') << endl;
      } else if (input == "q" || input == "quit") {
        cout << "Exiting client..." << endl;
        cout << string(80, '-') << endl;
        exit(0);
      } else {
        output = ccH.execute(ih.parseInput(input));
        cout << string(80, '-') << "\n" << output << "\n";
        cout << string(80, '-') << "\n";
      }

      // exceptions...
		} catch (InputException& e) {
      cout << e.msg << endl;

    } catch (NGDoesNotExistException& e) {
      cout << e.msg << endl;

    } catch (NGExistsException& e) {
      cout << e.msg << endl;

    } catch (ArticleDoesNotExistException& e) {
      cout << e.msg << endl;

    } catch (InvalidPathException& e) {
      cout << e.msg << endl;

    } catch (exception& e) {
			cout << " Error: Something went wrong. Client is closing." << endl;
			exit(1);
		}
	}
}
