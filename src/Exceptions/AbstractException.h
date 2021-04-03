#ifndef ABSTRACT_EXCEPTION_H
#define ABSTRACT_EXCEPTION_H

#include <string>

class AbstractException {
protected:
	std::string message = "\n";
public:
	AbstractException() = default;
	AbstractException(const std::string message);
	virtual const char* what() const throw() = 0;
};

#endif
