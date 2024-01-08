#pragma once
#include "adminService.h"
#include "eventRepository.h"
#include <cassert>
#include "memoryEventRepository.h"
#include "csvShortlist.h"
#include "userService.h"
#include "fakeRepository.h"
#include "eventRepository.h"
#include <iostream>
#include <QDebug>
#include "fakeEventValidator.h"

void testAdminService() {
	MemoryEventRepository repository{};
	AdminService service(&repository);

	Event party("Party", "some party", "2025.06.22", "12:30", 1000, "party.ro", 1);
	service.add("Party", "some party", "2025.06.22", "12:30", 1000, "party.ro");
	std::vector<Event> allEvents = service.getAll();
	assert(allEvents[0].hasSameFieldsMaybeExceptId(party));
	
	Event concert("Concert", "some music", "2024.02.12", "07:30", 250, "cluj.ro", 2);
	service.add("Concert", "some music", "2024.02.12", "07:30", 250, "cluj.ro");

	service.removeById(allEvents[0].getId());  // we remove the event added 1st
	allEvents = service.getAll();
	assert(allEvents[0].hasSameFieldsMaybeExceptId(concert));
	assert(allEvents.size() == 1);

	service.update(allEvents[0].getId(), "The concert", "The some music", "2029.05.05", "22:25", 251, "cluj.ro");
	allEvents = service.getAll();
	assert(allEvents[0].getAttendance() == 251);
	assert(allEvents[0].getHour() == "22:25");
}

void testUserService() {
	MemoryEventRepository repository{};
	CSVShortlist shortlist{repository, "testList.csv"};
	UserService service(&repository, &shortlist);

	Event concert = Event("Concert", "some music", "2024.02.12", "07:30", 250, "cluj.ro", 1);
	Event party = Event("Party", "dancing", "2023.12.12", "07:45", 450, "cluj.da", 1);
	repository.add(concert);
	assert(service.getAllEventsInMonth(2)[0].hasSameFieldsMaybeExceptId(concert));
	repository.add(party);
	assert(service.getAllEventsInMonth(12).size() == 1);
	
	service.addShortlist(service.getAllEventsInMonth(2)[0].getId());  // Concert
	std::vector<Event> interestedIn = service.getEventsInShortlist();
	std::vector<Event> allInMonthTwo = service.getAllEventsInMonth(2);
	assert(interestedIn[0].getLink() == allInMonthTwo[0].getLink());
	assert(service.getEventsInShortlist()[0].getMonth() == service.getAllEventsInMonth(2)[0].getMonth());
	//assert(service.interestedInIds[0] == service.getAllEventsInMonth(2)[0].getId());

	service.addShortlist(service.getAllEventsInMonth(12)[0].getId());  // Party
	service.deleteShortlist(service.getAllEventsInMonth(2)[0].getId());
	assert(service.getEventsInShortlist().size() == 1);
	assert(service.getEventsInShortlist()[0].getHour() == "07:45");

	std::vector<Event> allEventsMonthMinusOne = service.getAllEventsInMonth(-1);  // should be all
	assert(allEventsMonthMinusOne.size() == 2);
	assert(allEventsMonthMinusOne[0].hasSameFieldsMaybeExceptId(party) || allEventsMonthMinusOne[1].hasSameFieldsMaybeExceptId(concert));

	try {
		service.deleteShortlist(12349); // id doesn't exit: throw DuplicateEventException
		assert(false);
	}
	catch (...) {
		;
	}
}

void testEventRepository() {
	MemoryEventRepository repository{};

	Event concert("Concert", "some music", "2024.02.12", "07:30", 250, "cluj.ro", 1);
	Event party("Party", "dancing", "2023.12.12", "07:45", 450, "cluj.da", 1);
	
	repository.add(concert);
	assert(repository.existsEvent(concert));
	assert(repository.getAll().size() == 1);
	assert(repository.getAll()[0].hasSameFieldsMaybeExceptId(concert));
	
	repository.add(party);
	assert(repository.existsEvent(party));
	assert(repository.findById(1).hasSameFieldsMaybeExceptId(concert));
	assert(repository.findById(2).hasSameFieldsMaybeExceptId(party));

	assert(repository.nextId == 2);
	assert(repository.events[0].hasSameFieldsMaybeExceptId(concert) || repository.events[1].hasSameFieldsMaybeExceptId(concert));
	assert(repository.events[0].hasSameFieldsMaybeExceptId(party) || repository.events[1].hasSameFieldsMaybeExceptId(party));

	repository.decrementAttendance(1);  // Concert
	repository.incrementAttendance(2);  // Party

	assert(repository.findById(2).getAttendance() == 451);

	Event untold("Untold", "10th edition", "2023.08.08", "21:00", 15006, "cluj.ro", 5);
	repository.update(2, untold);
	assert(repository.findById(2).hasSameFieldsMaybeExceptId(untold));
	assert(repository.existsEvent(untold));

	repository.remove(concert);
	assert(repository.getAll().size() == 1);
	assert(repository.getAll()[0].hasSameFieldsMaybeExceptId(untold));
	assert(repository.events[0].hasSameFieldsMaybeExceptId(untold));

	MemoryEventRepository repositoryCopy(repository);
	assert(repositoryCopy.existsEvent(untold));
	assert(repositoryCopy.getAll()[0].hasSameFieldsMaybeExceptId(untold));
}

void testEvent() {
	Event untold("Untold", "10th edition", "2023.08.08", "21:00", 15006, "cluj.ro", 5);
	assert(untold.getAttendance() == 15006);
	assert(untold.getDate() == "2023.08.08");
	assert(untold.getHour() == "21:00");
	assert(untold.getId() == 5);
	assert(untold.getLink() == "cluj.ro");
	assert(untold.getMonth() == 8);

	assert(untold.toString().size() > 105);  // the ---..-

	Event emptyEvent;
	assert(emptyEvent.timeDate == "1970.01.01");
}

void testUserServicesGetAllEventsInMonthWithAFakeRepository() {
	FakeRepository* fakeRepoReturningNothing = new FakeRepository{};
	fakeRepoReturningNothing->returnsSomethingAtGetAll = false;
	FileShortlist* useless{};
	
	UserService userService{ dynamic_cast<EventRepository*>(fakeRepoReturningNothing),  useless };

	assert(userService.getAllEventsInMonth(-1).empty());
	assert(userService.getAllEventsInMonth(3).empty());
	assert(userService.getAllEventsInMonth(7).empty());

	FakeRepository* fakeRepoReturningTwoAprilsAndOneDecember = new FakeRepository{};
	fakeRepoReturningTwoAprilsAndOneDecember->returnsSomethingAtGetAll = true;
	fakeRepoReturningTwoAprilsAndOneDecember->monthToReturnOneOfAtGetAll = 12;
	fakeRepoReturningTwoAprilsAndOneDecember->monthToReturnTwoOfAtGetAll = 4;

	userService = UserService{ dynamic_cast<EventRepository*>(fakeRepoReturningTwoAprilsAndOneDecember),  useless };

	assert(userService.getAllEventsInMonth(-1).size() == 3);
	assert(userService.getAllEventsInMonth(12).size() == 1);
	assert(userService.getAllEventsInMonth(12)[0].getMonth() == 12);
	assert(userService.getAllEventsInMonth(4).size() == 2);
	assert(userService.getAllEventsInMonth(10).empty());
	assert(userService.getAllEventsInMonth(4)[0].getDate() <= userService.getAllEventsInMonth(4)[1].getDate());
}

void testAdminServicesAddsValidationUsingAFakeValidatorWhichDoesWhatItIsToldToDo() {
	FakeEventValidator* validatorWhichThrows = new FakeEventValidator{};
	validatorWhichThrows->alwaysThrowsOrNeverThrows = true;

	EventRepository eventRepository{};
	AdminService adminService{ &eventRepository, validatorWhichThrows };

	try {
		adminService.add("title", "desc", "timeda", "timeho", 100, "da.com");
		assert(false);
	}
	catch (EventException) {};
	assert(adminService.didAddEverThrowAtValidation);

	FakeEventValidator* quietValidator = new FakeEventValidator{};
	quietValidator->alwaysThrowsOrNeverThrows = false;
	AdminService serviceTheSecond{ &eventRepository, quietValidator };

	try {
		serviceTheSecond.add("title", "desc", "timeda", "timeho", 130, "da.com");
	}
	catch (EventException) {
		assert(false);
	}
	assert(!serviceTheSecond.didAddEverThrowAtValidation);
}
