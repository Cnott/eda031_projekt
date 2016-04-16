#include "clientcommandhandler.h"

using namespace std;


string ClientCommandHandler::update(pair<int,vector<string> > input){
  int cmd = input.first;
  switch (cmd) {
    case Protocol::COM_LIST_NG:     // list newsgroups
      return listNewsgroups();
      break;
    case Protocol::COM_CREATE_NG:   // create newsgroup
      createNewsGroup(input.second);
      break;
    case Protocol::COM_DELETE_NG:   // delete newsgroup
      deleteNewsGroup(input.second);
      break;
    case Protocol::COM_LIST_ART:    // list articles
      listArticles(input.second);
      break;
    case Protocol::COM_CREATE_ART:  // create article
      createArticle(input.second);
      break;
    case Protocol::COM_DELETE_ART:  // delete article
      deleteArticle(input.second);
      break;
    case Protocol::COM_GET_ART:     // get article
      getArticle(input.second);
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
  msH.recvCode();
  int nbrNgs=msH.recvInt();
  string result;
  for(int i=0;i!=nbrNgs;i++){
    msH.recvIntParameter();
    result+=msH.recvStringParameter();
  }
  return result;
}

string ClientCommandHandler::createNewsGroup(vector<string> &input){
  msH.sendCode(Protocol::COM_CREATE_NG);
  msH.sendStringParameter(input[0]);
  msH.sendCode(Protocol::COM_END);


  cout << "got here.." << endl;
  msH.recvCode();
  if(msH.recvCode()==Protocol::ANS_ACK){
    //it worked
  }
}
string ClientCommandHandler::deleteNewsGroup(vector<string> &input){
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  msH.recvCode();
  int nbrNgs=msH.recvInt();
  int id=-1;
  int tempId;
  for(int i=0;i!=nbrNgs;i++){
    tempId=msH.recvIntParameter();
    if(msH.recvStringParameter()==input[0]){
      id=tempId;
    }
  }
  if(id!=-1){
    msH.sendCode(Protocol::COM_DELETE_NG);
    msH.sendIntParameter(id);
    msH.sendCode(Protocol::COM_END);
  }

  msH.recvCode();
  if(msH.recvCode()==Protocol::ANS_ACK){
    //it worked
  }
}
string ClientCommandHandler::listArticles(vector<string> &input){
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  msH.recvCode();
  int nbrNgs=msH.recvInt();
  int id=-1;
  int tempId;
  for(int i=0;i!=nbrNgs;i++){
    tempId=msH.recvIntParameter();
    if(msH.recvStringParameter()==input[0]){
      id=tempId;
    }
  }

  if(id!=-1){
    msH.sendCode(Protocol::COM_LIST_ART);
    msH.sendIntParameter(id);
    msH.sendCode(Protocol::COM_END);
  }

  //måste hämta svaret
}
string ClientCommandHandler::createArticle(vector<string> &input){
  //måste först hämta idt på gruppen
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  msH.recvCode();
  int nbrNgs=msH.recvInt();
  int id=-1;
  int tempId;
  for(int i=0;i!=nbrNgs;i++){
    tempId=msH.recvIntParameter();
    if(msH.recvStringParameter()==input[0]){
      id=tempId;
    }
  }
  if(id!=-1){
    msH.sendCode(Protocol::COM_CREATE_ART);
    msH.sendIntParameter(id);
    msH.sendStringParameter(input[1]);  //title
    msH.sendStringParameter(input[2]); //author
    msH.sendStringParameter(input[3]);//text
    msH.sendCode(Protocol::COM_END);
  }
  msH.recvCode();
  if(msH.recvCode()==Protocol::ANS_ACK){
    //it worked
  }
}
string ClientCommandHandler::deleteArticle(vector<string> &input){
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  msH.recvCode();
  int nbrNgs=msH.recvInt();
  int id=-1;
  int tempId;
  for(int i=0;i!=nbrNgs;i++){
    tempId=msH.recvIntParameter();
    if(msH.recvStringParameter()==input[0]){
      id=tempId;
    }
  }
  if(id!=-1){
    msH.sendCode(Protocol::COM_DELETE_ART);
    msH.sendIntParameter(id);
    msH.sendIntParameter(stoi(input[1]));
    msH.sendCode(Protocol::COM_END);

    msH.recvCode();
  }
}
string ClientCommandHandler::getArticle(vector<string> &input){
  msH.sendCode(Protocol::COM_LIST_NG);
  msH.sendCode(Protocol::COM_END);

  msH.recvCode();
  int nbrNgs=msH.recvInt();
  int id=-1;
  int tempId;
  for(int i=0;i!=nbrNgs;i++){
    tempId=msH.recvIntParameter();
    if(msH.recvStringParameter()==input[0]){
      id=tempId;
    }
  }
  if(id!=-1){
    msH.sendCode(Protocol::COM_GET_ART);
    msH.sendIntParameter(id);
    msH.sendIntParameter(stoi(input[1]));
    msH.sendCode(Protocol::COM_END);

    msH.recvCode();
    string result;
    if(msH.recvCode()==Protocol::ANS_ACK){
        result+=msH.recvStringParameter();
    }
  }
}
