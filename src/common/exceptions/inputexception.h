#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H
#include <string>

struct InputException {
	std::string msg = "Input is not a recognizable command.";
};

#endif
