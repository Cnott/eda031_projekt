#include "clientcommandhandler.h"

using namespace std;


string ClientCommandHandler::update(pair<int,vector<string> > input){
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
      // not really needed atm, but keeping "in case shit"
      break;
  }
}
/**
*
*COM_LIST_NG COM_END
*
**/
string ClientCommandHandler::listNewsgroups(){
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  //hämtar resultatet
  if (msH.recvCode() == Protocol::ANS_LIST_NG) {
      cout << "Server: Trying to list all newsgroups" << endl;
  }
  int nbrNgs = msH.recvIntParameter();
  string result;
  for(int i = 0; i != nbrNgs; i++){
    result.append(to_string(msH.recvIntParameter()) + ". ");
    result += msH.recvStringParameter() + "\n";
  }
  msH.recvCode(); // ANS_END
  return result;
}

string ClientCommandHandler::createNewsGroup(vector<string> &input){
  msH.sendCode(Protocol::COM_CREATE_NG);
  msH.sendStringParameter(input[0]);
  msH.sendCode(Protocol::COM_END);

  if (msH.recvCode() == Protocol::ANS_CREATE_NG) {
    cout << "Server: Trying to create newsgroup " << input[0] << endl;
  };
  if(msH.recvCode()==Protocol::ANS_ACK){
    cout << "Succeeded" << endl;
  }
  msH.recvCode(); // ANS_END
  return input[0] + " added to the database";
}
string ClientCommandHandler::deleteNewsGroup(vector<string> &input){
  cout << "inside delete newsgroup in ccH" << endl;
  unsigned int ngId = stoul(input[0]);
  cout << "ngId: " << ngId << endl;
  msH.sendCode(Protocol::COM_DELETE_NG);
  msH.sendIntParameter(ngId);
  msH.sendCode(Protocol::COM_END);

  unsigned int tmp = msH.recvCode();
  if (tmp == Protocol::ANS_DELETE_NG) {
    cout << "Server: Trying to delete newsgroup" << endl;
  } else {
    cout << "Expected ANS_DELETE_NG, got " << tmp << endl;
  }

  if (msH.recvCode() == Protocol::ANS_ACK) {
    msH.recvCode(); // ANS_END
    return "Newsgroup " + to_string(ngId) + " deleted";
  } else if (msH.recvCode() == Protocol::ERR_NG_DOES_NOT_EXIST){
    msH.recvCode(); // ANS_END
    return "That newsgroup does not exist";
  }
  // int nbrNgs=msH.recvIntParameter();
  // int id=-1;
  // int tempId;
  // for(int i=0;i!=nbrNgs;i++){
  //   tempId=msH.recvIntParameter();
  //   if(msH.recvStringParameter()==input[0]){
  //     id=tempId;
  //   }
  // }
  // if(id!=-1){
  //   msH.sendCode(Protocol::COM_DELETE_NG);
  //   msH.sendIntParameter(id);
  //   msH.sendCode(Protocol::COM_END);
  // }
  //
  // msH.recvCode();
  // if(msH.recvCode()==Protocol::ANS_ACK){
  //   return input[0] + " removed from the database";
  // }
}
string ClientCommandHandler::listArticles(vector<string> &input){
  msH.sendCode(Protocol::COM_LIST_ART);
  msH.sendIntParameter(stoul(input[0]));
  msH.sendCode(Protocol::COM_END);

  if (msH.recvCode() == Protocol::ANS_LIST_ART) {
    cout << "Server: Trying to list all articles in newsgroup " << input[0] << endl;
  }

  string result = "";
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    int nbrNgs = msH.recvIntParameter();
    for (int i = 0; i != nbrNgs; i++) {
      result.append(to_string(msH.recvIntParameter()) + ". ");
      result += msH.recvStringParameter() + "\n";
    }
  } else { //response was ANS_NAK
    // Behöver kanske hantera detta
    msH.recvCode(); // ERR_NG_DOES_NOT_EXIST
  }
  msH.recvCode(); //ANS_END
  return result;
}

string ClientCommandHandler::createArticle(vector<string> &input){
  //måste först hämta idt på gruppen
  msH.sendCode(Protocol::COM_CREATE_ART);
  msH.sendIntParameter(stoul(input[0]));
  for (int i = 1; i <= 3; i++) {
    msH.sendStringParameter(input[i]);
  }
  msH.sendCode(Protocol::COM_END);

  if (msH.recvCode() == Protocol::ANS_CREATE_ART) {
    cout << "Server: Trying to create article in newsgroup " << input[0] << endl;
  }
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    cout << input[1] << " by " << input[2] << " added to newsgroup " << input[0] << endl;
  } else { // ANS_NAK
    // Behöver säkert hanteras
    msH.recvCode(); //ERR_NG_DOES_NOT_EXIST
    cout << "Newsgroup " << input[0] << " does not exist" << endl;
  }

  msH.recvCode(); // ANS_END
  return "";
}
  // msH.recvCode();
  // int nbrNgs=msH.recvIntParameter();
  // int id=-1;
  // int tempId;
  // for(int i=0;i!=nbrNgs;i++){
  //   tempId=msH.recvIntParameter();
  //   if(msH.recvStringParameter()==input[0]){
  //     id=tempId;
  //   }
  // }
  // if(id!=-1){
  //   msH.sendCode(Protocol::COM_CREATE_ART);
  //   msH.sendIntParameter(id);
  //   msH.sendStringParameter(input[1]);  //title
  //   msH.sendStringParameter(input[2]); //author
  //   msH.sendStringParameter(input[3]);//text
  //   msH.sendCode(Protocol::COM_END);
  // }
  // msH.recvCode();
  // if(msH.recvCode()==Protocol::ANS_ACK){
  //   //it worked
  // }

string ClientCommandHandler::deleteArticle(vector<string> &input){
  msH.sendCode(Protocol::COM_DELETE_ART);
  auto ngId = stoul(input[0]);
  auto artId = stoul(input[1]);
  msH.sendIntParameter(ngId);
  msH.sendIntParameter(artId);
  msH.sendCode(Protocol::COM_END);

  if (msH.recvCode() == Protocol::ANS_DELETE_ART) {
    cout << "Server: Trying to delete article " << artId << " in newsgroup " << ngId << endl;
  }

  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    cout << "Article has been deleted" << endl;
  } else {
    response = msH.recvCode();
    if (response == Protocol::ERR_NG_DOES_NOT_EXIST) {
      cout << "Newsgroup " << ngId << " does not exist" << endl;
    } else { // ERR_ART_DOES_NOT_EXIST
      cout << "Article " << artId << " in newsgroup " << ngId << " does not exist" << endl;
    }
  }
  msH.recvCode(); // ANS_END




  // msH.recvCode();
  // int nbrNgs=msH.recvIntParameter();
  // int id=-1;
  // int tempId;
  // for(int i=0;i!=nbrNgs;i++){
  //   tempId=msH.recvIntParameter();
  //   if(msH.recvStringParameter()==input[0]){
  //     id=tempId;
  //   }
  // }
  // if(id!=-1){
  //   msH.sendCode(Protocol::COM_DELETE_ART);
  //   msH.sendIntParameter(id);
  //   msH.sendIntParameter(stoi(input[1]));
  //   msH.sendCode(Protocol::COM_END);
  //
  //   msH.recvCode();
  // }
  return "";
}
string ClientCommandHandler::getArticle(vector<string> &input){
  msH.sendCode(Protocol::COM_GET_ART);
  auto ngId = stoul(input[0]);
  auto artId = stoul(input[1]);
  msH.sendIntParameter(ngId);
  msH.sendIntParameter(artId);
  msH.sendCode(Protocol::COM_END);

  if (msH.recvCode() == Protocol::ANS_GET_ART) {
    cout << "Server: Trying to get article " << artId << " in newsgroup " << ngId << endl;
  }

  string result = "";
  auto response = msH.recvCode();
  if (response == Protocol::ANS_ACK) {
    result.append("Title: ");
    result += msH.recvStringParameter() + "\n";
    result.append("Author: ");
    result += msH.recvStringParameter() + "\n";
    result.append("Text: ");
    result += msH.recvStringParameter() + "\n";
  } else { //response was ANS_NAK
    // Behöver kanske hantera detta
    msH.recvCode(); // ERR_NG_DOES_NOT_EXIST
  }
  return result;
}
