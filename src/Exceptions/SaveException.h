#ifndef SAVE_EXCEPTION_H
#define SAVE_EXCEPTION_H

#include "AbstractException.h"

class SaveException: public AbstractException{
public:
	SaveException() = default;
	SaveException(const std::string message);
	const char* what() const throw();
};

#endif