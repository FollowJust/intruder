#include "SaveException.h"

SaveException::SaveException(const std::string message) {
	this->message = message;
}

const char* SaveException::what() const throw() {
	std::string out = "An error occured while saving. " + message;
	return out.c_str();
}