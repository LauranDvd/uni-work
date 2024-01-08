#pragma once
#include <exception>
#include <string>

class ShortlistException : std::exception {
protected:
	std::string message;

public:
	ShortlistException(const std::string& _message) : message{ _message } {}
	ShortlistException() : message{ "Something went wrong with the shortlist" } {};
	virtual ~ShortlistException() {}

	const char* what() {
		return message.c_str();
	};
};