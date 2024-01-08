#pragma once
#include "memoryEventRepository.h"
#include "eventValidator.h"

class AdminService {
private:
	EventRepository* repository;
	EventValidator* validator;

public:
	AdminService(EventRepository* repository) noexcept : repository{ repository } {
		validator = new EventValidator{};
	};
	AdminService(EventRepository* repository, EventValidator* validator) noexcept : repository{ repository }, validator{validator} {};

	void add(std::string title, std::string description, std::string timeDate, std::string timeHour, int numberOfPeopleAttending, std::string socialMediaLink);
	std::vector<Event> getAll() const;

	void removeById(int id);
	void update(int id, std::string title, std::string description, std::string timeDate, std::string timeHour, int numberOfPeopleAttending, std::string socialMediaLink);

	int numberOfEventsInMonth(int month) const;

	friend void testAdminService();

	bool didAddEverThrowAtValidation = false;
};
