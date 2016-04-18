/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** inputexception.h
**
** Exception to be thrown when the client recieves invalid input from
** the user.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H
#include <string>

struct InputException {
	std::string msg = "Input is not a recognizable command.";
};

#endif	// INPUT_EXCEPTION_H
