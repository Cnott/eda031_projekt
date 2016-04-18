#ifndef NGDOESNOTEXISTEXCEPTION_H
#define NGDOESNOTEXISTEXCEPTION_H
#include <string>

struct NGDoesNotExistException{
	NGDoesNotExistException(std::string ngId) {
		msg = "The newsgroup with id " + ngId + " does not exist.";
	}
	std::string msg;
};

#endif
