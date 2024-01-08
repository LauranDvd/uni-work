#include "adminService.h"
#include <cassert>
#include <string>
#include "event.h"
#include <algorithm>

void AdminService::add(std::string title, std::string description, std::string timeDate, std::string timeHour, int numberOfPeopleAttending, std::string socialMediaLink) {
	Event gathering{ title, description, timeDate, timeHour, numberOfPeopleAttending, socialMediaLink, 0 };
	try {
		validator->validate(gathering);
	}
	catch (EventException& caught) {
		didAddEverThrowAtValidation = true;
		throw(caught);
	}
	repository->add(gathering);
}

std::vector<Event> AdminService::getAll() const {
	return repository->getAll();
}

void AdminService::removeById(int id) {
	Event gathering = repository->findById(id);
	repository->remove(gathering);
}

void AdminService::update(int id, std::string title, std::string description, std::string timeDate, std::string timeHour, int numberOfPeopleAttending, std::string socialMediaLink) {
	Event newEvent = Event{ title, description, timeDate, timeHour, numberOfPeopleAttending, socialMediaLink, id };
	validator->validate(newEvent);
	repository->update(id, newEvent);
}

int AdminService::numberOfEventsInMonth(int month) const {
	auto allEvents = repository->getAll();
	return count_if(allEvents.begin(), allEvents.end(), [&month](const Event& gathering) {
		return gathering.getMonth() == month;
		});
}
