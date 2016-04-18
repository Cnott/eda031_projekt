/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** ngexistsexception.h
**
** Exception to be thrown when the client tries to create a newsgroup
** that already exists.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef NG_EXISTS_EXCEPTION_H
#define NG_EXISTS_EXCEPTION_H
#include <string>

struct NGExistsException {
	NGExistsException(std::string ngId) {
		msg = "The newsgroup with id " + ngId + " already exist.";
	}
	std::string msg;
};

#endif // NG_EXISTS_EXCEPTION_H
