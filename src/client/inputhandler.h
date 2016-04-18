/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** inputhandler.h
** Recieves long string and translates the first words into command and
** remaining content related to the command.
** Returns a pair with int and a string. (int command, string content)
** the client follows same protocol as the server. i.e. protocol.h
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

/*-------------------------------------
    I N C L U D E S
-------------------------------------*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

#include "../common/protocol.h"
#include "../common/exceptions/inputexception.h"
#include "../common/exceptions/invalidpathexception.h"
/*-------------------------------------
    D E C L A R A T I O N S
-------------------------------------*/


/*-------------------------------------
    C L A S S   D E F
-------------------------------------*/
class InputHandler {
public:
  InputHandler();
  std::pair<int, std::vector<std::string> > parseInput(std::string);
private:
  std::vector<std::string> splitBySpace(std::string);
  int parseCommand(std::vector<std::string>) throw (InputException);
  std::string combineContent(std::vector<std::string>);
  std::pair<int, std::vector<std::string> > returnParsed(std::vector<std::string>) throw (InputException, InvalidPathException);
  std::vector<std::string> readFromFile(std::string filePath) throw (InvalidPathException);

  bool isNumber(const std::string& s);
};

#endif
