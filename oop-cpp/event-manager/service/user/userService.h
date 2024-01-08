#pragma once
#include "eventRepository.h"
#include "fileShortlist.h"

class UserService {
private: 
	EventRepository* repository;
	FileShortlist* shortlist;
public:
	UserService(EventRepository* _repository, FileShortlist* _shortlist) noexcept :
		repository{ _repository }, shortlist{ _shortlist } {};

	std::vector<Event> getAllEventsInMonth(int month);
	std::vector<Event> getEventsInShortlist();
	void addShortlist(int eventId);
	void deleteShortlist(int eventId);
	std::string getShortlistPath() const;
	void seeShortlistExtern() const;

	friend void testUserService();
};
