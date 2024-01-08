#pragma once
#include <exception>
#include <string>

class EventRepositoryException : public std::exception {
protected:
	std::string message;

public:
	EventRepositoryException(const std::string& _message) : message{ _message } {}
	EventRepositoryException() : message{ "Something went wrong in the repository" } {};
	virtual ~EventRepositoryException() {}

	const char* what() {
		return message.c_str();
	};
};
