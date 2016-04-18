#ifndef INVALID_PATH_EXCEPTION_H
#define INVALID_PATH_EXCEPTION_H
#include <string>

struct InvalidPathException{
	InvalidPathException(std::string path) {
		msg = path + " is not a valid file path.";
	}
	std::string msg;
};

#endif
