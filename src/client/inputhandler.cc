#include "inputhandler.h"

using namespace std;

InputHandler::InputHandler() {
}

/* Parses the input from client and retuns a pair with the protocol as the
   first value and a vector of strings containing information to give the server
*/
pair<int, vector<string> > InputHandler::parseInput(string input) {
  vector<string> parameters = splitBySpace(input); //Splits input in order to identify commands
  if (parameters.size() == 0) {
    //wrong number of inputs
    vector<string> rsv = {};
    rsv.push_back("");
    return make_pair(Protocol::COM_END, rsv);
  }

  try {
    return returnParsed(parameters);
  } catch (InvalidPathException& e) {
    throw;
  }
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
pair<int, vector<string> > InputHandler::returnParsed(vector<string> parameters) throw (InputException, InvalidPathException){
  int p = parseCommand(parameters); // reads command-byte
  vector<string> rsv = {};       // the return string vector

  switch (p) {
    case Protocol::COM_CREATE_NG: { // create newsgroup
      string ngName = "";
      for (int i = 2; i < parameters.size(); i++){
        ngName.append(parameters[i]);
        if (i < parameters.size() -1) ngName.append(" ");
      }
      rsv.push_back(ngName); // the name of newsgroup
      break;
    }
    case Protocol::COM_DELETE_NG:   // delete newsgroup
      rsv.push_back(parameters[2]); // the name of newsgroup // changing to number...
      break;

    case Protocol::COM_LIST_ART:    // list articles
      rsv.push_back(parameters[1]); // the name of newsgroup
      break;

    case Protocol::COM_CREATE_ART:  // create article
      try {
      rsv = readFromFile(parameters[3]);
      rsv.insert(rsv.begin(), parameters[2]);
    } catch (InvalidPathException& e) {
      throw;
    }
      break;

    case Protocol::COM_DELETE_ART:  // delete article
      rsv.push_back(parameters[2]); // the name of the newsgroup
      rsv.push_back(parameters[3]); // the id of the article
      break;

    case Protocol::COM_GET_ART:     // get article
      rsv.push_back(parameters[1]);
      rsv.push_back(parameters[2]);
      break;
    case Protocol::COM_LIST_NG:     // list newsgroups
      rsv.push_back("");
      break;
    default:                        //list newsgroup and default return.
        throw InputException();
        break;
  }
  return make_pair(p,rsv);
}

/* Reads the first words of the input and translates them into the correct
   protocol. If the words does not match any protocol COM_END is returned.
*/
int InputHandler::parseCommand(vector<string> parameters) throw (InputException){
  int p = Protocol::COM_END; // if nothing matches return command end.
  string s = parameters[0];
  for (int i=0; s[i]; i++) s[i] = tolower(s[i]); //convert string to lowercase

  int nParam = parameters.size();

  if (s == "list") {
    if (nParam == 1) {
      p = Protocol::COM_LIST_NG;
    } else if (nParam == 2 && isNumber(parameters[1])) {
      p = Protocol::COM_LIST_ART;
    } else {
      throw InputException();
    }
  }

  if (s == "create" && nParam > 2) {
    if (parameters[1] == "newsgroup"){
      p = Protocol::COM_CREATE_NG;
    } else if (parameters[1] == "article" &&  isNumber(parameters[2]) && nParam == 4) {
      p = Protocol::COM_CREATE_ART;
    } else {
      throw InputException();
    }
  }

  if (s == "delete" && nParam > 2){
    if (!isNumber(parameters[1]) && isNumber(parameters[2])) {
      if (parameters[1] == "newsgroup" && nParam == 3){
        p = Protocol::COM_DELETE_NG;
      } else if (parameters[1] == "article" && nParam == 4 && isNumber(parameters[3])) {
        p = Protocol::COM_DELETE_ART;
      } else {
        throw InputException();
      }
    }
  }

  if (s == "get" && nParam == 3 && isNumber(parameters[1]) && isNumber(parameters[2]))
    p = Protocol::COM_GET_ART;

  return p;
}

/* Reads an article from file and gives the information contained to the server
   The first row is the title, second is the author and the remaining rows are
   the text of the article.
*/
vector<string> InputHandler::readFromFile(string filePath) throw (InvalidPathException){
  /* Reads file content from file into string */
  ifstream file(filePath.c_str());
  if (!file.is_open()) {
    throw InvalidPathException(filePath);
  }
  stringstream buffer;
  buffer << file.rdbuf();
  string fileCon = buffer.str();

  /* Find first row and save as new string then remove from fileCon */
  string title(fileCon.begin(),find(fileCon.begin(),fileCon.end(),'\n'));
  fileCon.erase(fileCon.begin(),find(fileCon.begin(),fileCon.end(),'\n')+1);
  string author(fileCon.begin(), find(fileCon.begin(), fileCon.end(),'\n'));
  fileCon.erase(fileCon.begin(),find(fileCon.begin(),fileCon.end(),'\n')+1);

  /* Save rest of string as text. */
  string text = fileCon;

  /* Adds strings to vector and returns */
  vector<string> rsv = {title, author, text};
  return rsv;
}

bool InputHandler::isNumber(const string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
