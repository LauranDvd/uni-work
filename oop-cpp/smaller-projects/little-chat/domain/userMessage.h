#pragma once
#include <string>
#include "user.h"

class UserMessage {
private:
	std::pair<std::string, User> data;

public:
	UserMessage(std::string message, User user) : data{ message, user } {};

	std::string getMessage() const { return data.first; }
	User getUser() const { return data.second; }
};