#ifndef NGEXISTSEXCEPTION_H
#define NGEXISTSEXCEPTION_H
#include <string>

struct NGExistsException {
	NGExistsException(std::string ngId) {
		msg = "The newsgroup with id " + ngId + " already exist.";
	}
	std::string msg;
};

#endif
