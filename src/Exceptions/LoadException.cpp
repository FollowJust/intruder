#include "LoadException.h"

LoadException::LoadException(const std::string message) {
	this->message = message;
}

const char* LoadException::what() const throw() {
	std::string out = "An error occured while loading. " + message;
	return out.c_str();
}