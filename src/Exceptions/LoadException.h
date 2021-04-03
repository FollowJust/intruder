#ifndef LOAD_EXCEPTION_H
#define LOAD_EXCEPTION_H

#include "AbstractException.h"

class LoadException: public AbstractException {
public:
	LoadException() = default;
	LoadException(const std::string message);
	const char* what() const throw();
};

#endif
