#include "fakeRepository.h"

std::vector<Event> FakeRepository::getAll() const {
	if (!returnsSomethingAtGetAll)
		return std::vector<Event>(0);

	std::string singleMonth = std::to_string(monthToReturnOneOfAtGetAll);
	if (singleMonth.size() == 1)
		singleMonth = "0" + singleMonth;
	std::string doubleMonth = std::to_string(monthToReturnTwoOfAtGetAll);
	if (doubleMonth.size() == 1)
		doubleMonth = "0" + doubleMonth;

	Event fakeEventOne{ "Bad", "This event will be", "2020." + singleMonth + ".04", "19:30", 200, "a.com", 33 };
	Event fakeEventTwo{ "Good", "This event will be", "2022." + doubleMonth + ".09", "19:30", 300, "a.com", 33 };
	Event fakeEventThree{ "Good", "Tent wildasdjaslkdwal be", "2021." + doubleMonth + ".09", "21:15", 300, "a.com", 33 };

	return std::vector<Event>{fakeEventOne, fakeEventTwo, fakeEventThree};
}
