#pragma once
#include <vector>
#include <string>
#include "event.h"

class EventException {
private:
	std::vector<std::string> problems;

public:
	EventException(std::vector<std::string> _problems) : problems{ _problems } {}
	
	std::vector<std::string> getProblems() const { return problems; }
};


class EventValidator {
private:
	static bool isValidDate(std::string mayBeDate);
	static bool isValidHour(std::string mayBeHour);
public:
	EventValidator() {}

	virtual void validate(const Event& gathering);
};