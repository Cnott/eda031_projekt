/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** ngdoesnotexistexception.h
**
** Exception to be thrown when the client tries to access a non-existant
** newsgroup.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef NG_DOES_NOT_EXIST_EXCEPTION_H
#define NG_DOES_NOT_EXIST_EXCEPTION_H
#include <string>

struct NGDoesNotExistException{
	NGDoesNotExistException(std::string ngName) {
		msg = "The newsgroup " + ngName + " does not exist.";
	}
	std::string msg;
};

#endif // NG_DOES_NOT_EXIST_EXCEPTION_H
