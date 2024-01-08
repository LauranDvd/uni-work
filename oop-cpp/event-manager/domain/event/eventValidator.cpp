#include "eventValidator.h"
#include <algorithm>
#include "constants.h"
#include "utilities.h"

bool EventValidator::isValidDate(std::string mayBeDate) {
	// 2012.05.29 format
	if (mayBeDate.size() != 4 + 1 + 2 + 1 + 2)
		return false;

	bool digitWhereShouldBe = true;
	int currentIndex = 0;
	for_each(mayBeDate.begin(), mayBeDate.end(), [&digitWhereShouldBe, &currentIndex](char isInMayBeDate) {
		if (currentIndex != DATE_FIRST_SEPARATOR_INDEX && currentIndex != DATE_SECOND_SEPARATOR_INDEX &&
			!('0' <= isInMayBeDate && isInMayBeDate <= '9'))
			digitWhereShouldBe = false;
		currentIndex++;
		});
	if (!digitWhereShouldBe)
		return false;

	int month = stringToInt(mayBeDate.substr(5, 2)), day = stringToInt(mayBeDate.substr(8, 2));
	if (month < 1 || month > 12 || day < 1 || day > 31)  // not 100% correct
		return false;

	return true;
}

bool EventValidator::isValidHour(std::string mayBeHour) {
	// 16:52-like format
	if (mayBeHour.size() != 5)
		return false;

	bool digitWhereShouldBe = true;
	int currentIndex = 0;
	for_each(mayBeHour.begin(), mayBeHour.end(), [&digitWhereShouldBe, &currentIndex](char isInMayBeHour) {
		if (currentIndex != HOUR_SEPARATOR_INDEX && !('0' <= isInMayBeHour && isInMayBeHour <= '9'))
			digitWhereShouldBe = false;
		currentIndex++;
		});
	if (!digitWhereShouldBe)
		return false;

	int hour = stringToInt(mayBeHour.substr(0, 2)), minute = stringToInt(mayBeHour.substr(3, 2));
	if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
		return false;

	return true;
}

void EventValidator::validate(const Event& gathering) {
	std::vector<std::string> theProblems;

	// title, description, link: can be anything
	if (gathering.getTitle().size() == 0 || gathering.getDescription().size() == 0 || gathering.getLink().size() == 0)
		theProblems.push_back("Some fields were left empty");

	// number of people attending: can be any integer
	
	// date, hour
	if (!isValidDate(gathering.getDate()))
		theProblems.push_back("The date is not valid.");
	if (!isValidHour(gathering.getHour()))
		theProblems.push_back("The hour is not valid.");

	if (!theProblems.empty())
		throw(EventException(theProblems));
}
