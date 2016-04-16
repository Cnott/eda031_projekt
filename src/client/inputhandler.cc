#include "inputhandler.h"

using namespace std;

/* Parses the input from client and retuns a pair with the protocol as the
   first value and a vector of strings containing information to give the server
*/

InputHandler::InputHandler() {

}

pair<int, vector<string> > InputHandler::parseInput(string input) {
  vector<string> parameters = splitBySpace(input); //Splits input in order to identify commands
  if (parameters.size() == 0 || parameters.size() > 4) {
    //wrong number of inputs
    vector<string> rsv = {};
    rsv.push_back("");
    return make_pair(Protocol::COM_END, rsv);
  }
  return returnParsed(parameters);
}

/* Splits the input string by space characters */
vector<string> InputHandler::splitBySpace(string s) {
  string buf; // buffer string
  stringstream ss(s); // insert into a stringstream
  vector<string> tokens; // output vector
  while (ss >> buf)
    tokens.push_back(buf);
  return tokens;
}

/* Fills the return string vector with content from commandline depending on
   the command given in first words. */
pair<int, vector<string> > InputHandler::returnParsed(vector<string> parameters) {
  int p = parseCommand(parameters); // reads command-byte
  vector<string> rsv = {};       // the return string vector

  switch (p) {
    case Protocol::COM_CREATE_NG:   // create newsgroup
      rsv.push_back(parameters[2]); // the name of newsgroup
      break;

    case Protocol::COM_DELETE_NG:   // delete newsgroup
      cout << parameters[1] << endl;
      rsv.push_back(parameters[1]); // the name of newsgroup // changing to number...
      break;

    case Protocol::COM_LIST_ART:    // list articles
      rsv.push_back(parameters[1]); // the name of newsgroup
      break;

    case Protocol::COM_CREATE_ART:  // create article
      rsv = readFromFile(parameters[3]);
      rsv.insert(rsv.begin(), parameters[2]);
      break;

    case Protocol::COM_DELETE_ART:  // delete article
      rsv.push_back(parameters[2]); // the name of the newsgroup
      rsv.push_back(parameters[3]); // the id of the article
      break;

    case Protocol::COM_GET_ART:     // get article
      rsv.push_back(parameters[1]);
      break;

    default:                        //list newsgroup and default return.
        rsv.push_back("");
        break;
  }
  return make_pair(p,rsv);
}

/* Reads the first words of the input and translates them into the correct
   protocol. If the words does not match any protocol COM_END is returned.
*/
int InputHandler::parseCommand(vector<string> parameters) {
  int p = Protocol::COM_END; // if nothing matches return command end.
  string s = parameters[0];
  for (int i=0; s[i]; i++) s[i] = tolower(s[i]); //convert string to lowercase

  if (s == "list"   && parameters.size() == 1)
                        p = Protocol::COM_LIST_NG;
  if (s == "list"   && parameters.size() != 1)
                        p = Protocol::COM_LIST_ART;
  if (s == "create" && parameters[1] == "article")
                        p = Protocol::COM_CREATE_ART;
  if (s == "create" && parameters[1] == "newsgroup")
                        p = Protocol::COM_CREATE_NG;
  if (s == "delete" && parameters.size() == 2)
                        p = Protocol::COM_DELETE_NG;
  if (s == "delete" && parameters.size() != 2)
                        p = Protocol::COM_DELETE_ART;
  if (s == "get")
                        p = Protocol::COM_GET_ART;
  return p;
}

/* Reads an article from file and gives the information contained to the server
   The first row is the title, second is the author and the remaining rows are
   the text of the article.
*/
vector<string> InputHandler::readFromFile(string filePath) {
  string line;
  ifstream myFile (filePath);
  vector<string> rsv;           //return string vector

  //ifstream file(input.c_str());
  //stringstream buffer;
  //buffer << file.rdbuf();
  //string str = buffer.str();

  if (myFile.is_open()) {
    for (int i = 1; i != 3; i++) { //adds first two lines i.e. title & author
      getline(myFile, line);
      rsv.push_back(line);
    }
    string buff = "";
    while (getline(myFile,line)) {
      buff += line;
    }
    rsv.push_back(buff);          // adds remaining lines i.e. text
    myFile.close();
  }
  return rsv;
}
