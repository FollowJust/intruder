#include "FileException.h"

FileException::FileException(const std::string message) {
	this->message = message;
}

const char* FileException::what() const throw() {
	std::string out = "An error occured while managing the file. " + message;
	return out.c_str();
}