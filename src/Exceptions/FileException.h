#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H

#include "AbstractException.h"

class FileException : public AbstractException {
public:
	FileException() = default;
	FileException(const std::string message);
	const char* what() const throw();
};

#endif
