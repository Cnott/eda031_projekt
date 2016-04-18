#include "clientcommandhandler.h"

using namespace std;

bool DEBUG = true;

/*  This is the method that the client executes, after parsing input with
    the inputhandler. The methods' purpose is fairly self-explanatory.

    In general they check to receive if the correct input is returned from the
    client, after which the responses from the server, via the
    ServerCommandHandler are used to determine how to answer the client.

    A simple switch case is executed to determine which Protocol to follow.
    For more info on the Protocols, see servercommandhandler.cc and protocol.h
*/

string ClientCommandHandler::execute(pair<int,vector<string> > input){
  int cmd = input.first;
  switch (cmd) {
    case Protocol::COM_LIST_NG:     // list newsgroups
      return listNewsgroups();
      break;
    case Protocol::COM_CREATE_NG:   // create newsgroup
      return createNewsGroup(input.second);
      break;
    case Protocol::COM_DELETE_NG:   // delete newsgroup
      return deleteNewsGroup(input.second);
      break;
    case Protocol::COM_LIST_ART:    // list articles
      return listArticles(input.second);
      break;
    case Protocol::COM_CREATE_ART:  // create article
      return createArticle(input.second);
      break;
    case Protocol::COM_DELETE_ART:  // delete article
      return deleteArticle(input.second);
      break;
    case Protocol::COM_GET_ART:     // get article
      return getArticle(input.second);
      break;
    case Protocol::COM_END:         // command end
      break;
  }
}

string ClientCommandHandler::listNewsgroups(){
  // messages to server
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  // messages from server
  if (msH.recvCode() == Protocol::ANS_LIST_NG) {
    if (DEBUG)
      cout << "Server: Trying to list all newsgroups" << endl;
  }
  int nbrNgs = msH.recvIntParameter();
  string result;
  for(int i = 0; i != nbrNgs; i++){
    result.append(to_string(msH.recvIntParameter()) + ". ");
    result.append(msH.recvStringParameter());
    if (i != nbrNgs - 1)
      result.append("\n");
  }
  msH.recvCode(); // ANS_END
  return result;
}

string ClientCommandHandler::createNewsGroup  (vector<string> &input)
                                              throw (NGExistsException){
  // messages to server
  msH.sendCode(Protocol::COM_CREATE_NG);
  msH.sendStringParameter(input[0]);
  msH.sendCode(Protocol::COM_END);
// messages from server
  if (msH.recvCode() == Protocol::ANS_CREATE_NG) {
    if (DEBUG)
      cout << "Server: Trying to create newsgroup " << input[0] << endl;
  }
  string result = "";
  auto response = msH.recvCode();
  if(response == Protocol::ANS_ACK){
    result.append("Newsgroup nr. " + input[0] + " added to the database.");
    if (DEBUG)
      cout << "Succeeded" << endl;
  } else if (response == Protocol::ANS_NAK) {
      if (msH.recvCode() == Protocol::ERR_NG_ALREADY_EXISTS){
        msH.recvCode(); // ANS_END
        throw NGExistsException(input[0]);
      }
  }
  msH.recvCode(); // ANS_END
  return result;
}
string ClientCommandHandler::deleteNewsGroup  (vector<string> &input)
                                              throw (NGDoesNotExistException){
  // messages to server
  unsigned int ngId = stoul(input[0]);
  msH.sendCode(Protocol::COM_DELETE_NG);
  msH.sendIntParameter(ngId);
  msH.sendCode(Protocol::COM_END);

  // messages from server
  auto response = msH.recvCode();
  if (response == Protocol::ANS_DELETE_NG) {
    if (DEBUG)
      cout << "Server: Trying to delete newsgroup" << endl;
  } else {
    if (DEBUG)
      cout << "Expected ANS_DELETE_NG, got " << response << endl;
  }

  // successful?
  if (msH.recvCode() == Protocol::ANS_ACK) {
    msH.recvCode(); // ANS_END
    return "Newsgroup nr. " + to_string(ngId) + " deleted.";
  } else if (msH.recvCode() == Protocol::ERR_NG_DOES_NOT_EXIST){
      msH.recvCode(); // ANS_END
      throw NGDoesNotExistException(input[0]);
  } else {
    throw exception();  // If we get here, something went really wrong!
  }
}


string ClientCommandHandler::listArticles (vector<string> &input)
                                          throw (NGDoesNotExistException){
  // messages to server
  msH.sendCode(Protocol::COM_LIST_ART);
  msH.sendIntParameter(stoul(input[0]));
  msH.sendCode(Protocol::COM_END);

  // messages from server
  if (msH.recvCode() == Protocol::ANS_LIST_ART) {
    if (DEBUG)
      cout  << "Server: Trying to list all articles in newsgroup nr. "
            << input[0] << endl;
  }

  // successful?
  string result = "";
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    int nbrArt = msH.recvIntParameter();
    for (int i = 0; i != nbrArt; i++) {
      result.append(to_string(msH.recvIntParameter()) + ". ");
      result += msH.recvStringParameter();
      if (i != nbrArt - 1) result += "\n";
    }
  } else if (msH.recvCode() == Protocol::ERR_NG_DOES_NOT_EXIST){
    msH.recvCode(); //ANS_END
    throw NGDoesNotExistException(input[0]);
  }
  msH.recvCode(); //ANS_END
  return result;
}

string ClientCommandHandler::createArticle  (vector<string> &input)
                                            throw (NGDoesNotExistException){
  // messages to server
  msH.sendCode(Protocol::COM_CREATE_ART);
  msH.sendIntParameter(stoul(input[0]));
  for (int i = 1; i <= 3; i++) {
    msH.sendStringParameter(input[i]);
  }
  msH.sendCode(Protocol::COM_END);

  // messages from server
  if (msH.recvCode() == Protocol::ANS_CREATE_ART) {
    if (DEBUG)
      cout  << "Server: Trying to create article in newsgroup "
            << input[0] << endl;
  }

  // successful?
  string result = "";
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    result.append(input[1] + " by " + input[2] + " added to newsgroup nr. "
          + input[0] + ".");
  }  else if (msH.recvCode() == Protocol::ERR_NG_DOES_NOT_EXIST){
    msH.recvCode(); //ANS_END
    throw NGDoesNotExistException(input[0]);
  } else {
    throw exception();  // If we get here, something went really wrong!
  }

  msH.recvCode(); // ANS_END
  return result;
}

string ClientCommandHandler::deleteArticle(vector<string> &input)
                                           throw (NGDoesNotExistException,
                                                  ArticleDoesNotExistException){
  // messages to server
  msH.sendCode(Protocol::COM_DELETE_ART);
  auto ngId = stoul(input[0]);
  auto artId = stoul(input[1]);
  msH.sendIntParameter(ngId);
  msH.sendIntParameter(artId);
  msH.sendCode(Protocol::COM_END);

  // messages from server
  if (msH.recvCode() == Protocol::ANS_DELETE_ART) {
    if (DEBUG)
      cout  << "Server: Trying to delete article " << artId
            << " in newsgroup " << ngId << endl;
  }

  // successful?
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    msH.recvCode(); // ANS_END
    return "Article nr. " + to_string(artId) + " deleted from newsgroup nr. "
                + to_string(ngId) + ".";
  } else {
    response = msH.recvCode();
    msH.recvCode(); // ANS_END
    if (response == Protocol::ERR_NG_DOES_NOT_EXIST) {
      throw NGDoesNotExistException(input[0]);
    } else {
      throw ArticleDoesNotExistException(input[0], input[1]);
    }
  }
  msH.recvCode(); // ANS_END
  return "";
}

string ClientCommandHandler::getArticle (vector<string> &input)
                                        throw ( NGDoesNotExistException,
                                                ArticleDoesNotExistException){
  // messages to server
  msH.sendCode(Protocol::COM_GET_ART);
  auto ngId = stoul(input[0]);
  auto artId = stoul(input[1]);
  msH.sendIntParameter(ngId);
  msH.sendIntParameter(artId);
  msH.sendCode(Protocol::COM_END);

  // messages from server
  if (msH.recvCode() == Protocol::ANS_GET_ART) {
    if (DEBUG)
      cout  <<"Reading article nr." << artId <<" from newsgroup nr."
            <<ngId<<"."<<endl;
  }

  // succesful?
  string result = "";
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    result.append("Title : ");
    result += msH.recvStringParameter() + "\n" + string(80, '-') + "\n";
    result.append("Author: ");
    result += msH.recvStringParameter() + "\n" + string(80, '-') + "\n";
    result += msH.recvStringParameter() + "\n";
  } else { // ANS_NAK
    response = msH.recvCode();
    msH.recvCode(); // ANS_END
    if (response == Protocol::ERR_NG_DOES_NOT_EXIST) {
      if (DEBUG)
        cout << "Newsgroup " << ngId << " does not exist" << endl;

      throw NGDoesNotExistException(input[0]);
    } else if (response == Protocol::ERR_ART_DOES_NOT_EXIST){
        throw ArticleDoesNotExistException(input[0], input[1]);
    } else {
        throw exception();
    }
  }
  msH.recvCode(); // ANS_END
  return result;
}
