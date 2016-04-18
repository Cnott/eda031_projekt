#include <iostream>
#include "inputhandler.h"
#include "clientcommandhandler.h"
#include "../common/connection.h"
#include "../common/messagehandler.h"
#include "../common/exceptions/ngexistsexception.h"
#include "../common/exceptions/ngdoesnotexistexception.h"
#include "../common/exceptions/noarticleexception.h"
#include "../common/exceptions/invalidpathexception.h"

using namespace std;
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

  MessageHandler msH(conn);
  ClientCommandHandler ccH(msH);
  InputHandler ih;

  string info="This is a newsgroup client. Type 'help' for a list of commands.";
  string listN = "list:\t Lists newsgroups on server.";
  string listA = "list x:\t Lists articles on newsgroup number x.";
  string getA = "get x y:\t Retrieves article y from newsgroup x.";
  string createN = "create newsgroup x:\t Creates new newsgroup with name x.";
  string createA = "create article x path:\t Creates new article in "
                         "newsgroup x from the content\n\t\t\t of the file "
                         "specified. The file should have title\n\t\t\t on the "
                         "first row followed by the author on the\n\t\t\t "
                         "second and the text content on the remaining.";
  string deleteN = "delete newsgroup x:\t Deletes newsgroup x.";
  string deleteA = "delete article x y:\t Deletes article y from newsgroup x.";

  vector<string> helpInfo = {listN,listA,getA,createN,createA,deleteN,deleteA};

  cout << string(80, '-')  << endl << info << endl << string(80, '-') << endl;
	while (true) {
    cout << "Enter a command: ";
		try {
      string input;
      string output;
			getline(cin, input);
      if (input == "help") {
        for(auto it : helpInfo) {
          cout << it << endl;
        }
        cout << string(80, '-') << endl;
      } else {
        output = ccH.update(ih.parseInput(input));
        cout << string(80, '-') << "\n" << output << "\n";
        cout << string(80, '-') << "\n";
      }
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


    // cout<<"Hello"<<endl;
    // InputHandler ih;
    // pair<int, vector<string> > com;

    // com = ih.parseInput("list");
    // cout<< "This should be 1: " << com.first << endl;

    // com = ih.parseInput("create newsgroup newsgroup.wiki.com");
    // cout<< "This should be 2: " << com.first << endl;

    // com = ih.parseInput("delete newsgroup.wiki.com");
    // cout<< "This should be 3: " << com.first << endl;

    // com = ih.parseInput("list newsgroup.wiki.com");
    // cout<< "This should be 4: " << com.first << endl;

    // com = ih.parseInput("create article newsgroup.wiki.com /home/anton/Documents/Floobits/article.txt");
    // cout<< "This should be 5: " << com.first << endl;
    // cout<< "Newsgroup: " << com.second[0] << endl;
    // cout<< "This is the article read: \n" << "Title: " << com.second[1] << "\n";
    // cout<< "Author: " << com.second[2] << "\n";
    // cout<< "Text: " << com.second[3] << endl;

    // com = ih.parseInput("delete article newsgroup.wiki.com 1");
    // cout<< "This should be 6: " << com.first << endl;

    // com = ih.parseInput("get 1");
    // cout<< "This should be 7: " << com.first << endl;

    // com = ih.parseInput("");
    // cout<< "This should be 8: " << com.first << endl;

    // com = ih.parseInput("This not input");
    // cout<< "This should be 8: " << com.first << endl;
}

/*
 * Read a string from the server.
 */
