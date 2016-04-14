#include <string>
#include "connection.h"
#include "logger.h"
#include "messagehandler.h"
#include "connectionclosedexception.h"
#include "protocol.h"

using namespace std;


MessageHandler::MessageHandler(Connection &c){
    this->conn=&c;
}

MessageHandler::~MessageHandler(){

}

void MessageHandler::sendByte(int i) {
  try{
    conn->write(static_cast<char>(i));
  } catch(ConnectionClosedException&){
    //typ göra något här
  }
}

void MessageHandler::sendCode(int code) {
    try{
      conn->write(code);
    } catch(ConnectionClosedException){
      //Typ göra något här
    }
}

int MessageHandler::recvByte() {
  int code = conn->read();
  return code;
}


void MessageHandler::sendInt(int value) {
  sendByte((value >> 24) & 0xFF);
  sendByte((value >> 16) & 0xFF);
  sendByte((value >> 8) & 0xFF);
  sendByte(value & 0xFF);
}
void MessageHandler::sendIntParameter(int param) {
  sendCode(Protocol::PAR_NUM);
  sendInt(param);
}
void MessageHandler::sendStringParameter(string param) {
  sendCode(Protocol::PAR_STRING);
  sendInt(param.length());
  for (unsigned int i = 0; i < param.length(); i++) {
    sendByte(param.find(i));
  }
}
int MessageHandler::recvCode() {
  int code = recvByte();
  return code;
}
int MessageHandler::recvInt() {
  int b1 = recvByte();
  int b2 = recvByte();
  int b3 = recvByte();
  int b4 = recvByte();

  return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}
int MessageHandler::recvIntParameter() {
  int code = recvCode();
  /*
  if (code != Protocol.PAR_NUM) {
    throw new ProtocolViolationException("Receive numeric parameter",
        Protocol.PAR_NUM, code);
  }
  */
  return recvInt();
}
std::string MessageHandler::recvStringParameter() {
  /*
  int code = recvCode();
  if (code != Protocol.PAR_STRING) {
    throw new ProtocolViolationException("Receive string parameter",
        Protocol.PAR_STRING, code);
  }
  int n = recvInt();
  if (n < 0) {
    throw new ProtocolViolationException("Receive string parameter",
        "Number of characters < 0");
  }
  StringBuffer result = new StringBuffer(n);
  for (int i = 1; i <= n; i++) {
    char ch = (char) conn.read();
    result.append(ch);
    logWindow.logChar(ch);
  }
  return result.toString();*/
    return nullptr;
}
