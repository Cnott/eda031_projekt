/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** invalidpathexception.h
**
** Exception to be thrown when the client recieves an invalid file path
** from the user.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef INVALID_PATH_EXCEPTION_H
#define INVALID_PATH_EXCEPTION_H
#include <string>

struct InvalidPathException{
	InvalidPathException(std::string path) {
		msg = path + " is not a valid file path.";
	}
	std::string msg;
};

#endif	// INVALID_PATH_EXCEPTION_H
