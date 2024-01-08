#pragma once
#include <string>

class User {
private:
	std::string uniqueUserName;
	std::string name;

public:
	User(std::string uniqueUserName, std::string name) : uniqueUserName{ uniqueUserName }, name{ name } {}

	std::string getUniqueUserName() const { return uniqueUserName; }
	std::string getName() const { return name; }
};