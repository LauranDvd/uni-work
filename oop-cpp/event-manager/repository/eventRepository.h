#pragma once
#include <vector>
#include "event.h"

class EventRepository {
protected:
	std::vector<Event> events;
	int nextId;  // for the id's
public:
	EventRepository() noexcept : nextId{ 0 } {} 
	// copy constructor
	EventRepository(const EventRepository& repository);

	virtual ~EventRepository() {}

	// checks whether an event exists in the repository. comparison is done based on events' contents
	// (everything except the ids)
	// post: returns True if "gathering" exists, or False otherwise
	bool existsEvent(Event& gathering) const;

	// add event to the repository
	// post: "gathering" is in the repository. its id will not be preserved
	virtual void add(Event gathering);  // "event" is reserved
	
	// remove a given Event. comparison is done using Event's equality operator
	// pre: an event equal to "gathering" exists in the repository
	// post: it no longer exists
	virtual void remove(const Event& gathering);

	virtual std::vector<Event> getAll() const;
	Event findById(int id) const;
	bool existsId(int id) const;

	// update event with given id. the new event will keep the id of the old one (regardless of the id of the provided event) 
	// pre: there is an event with id "id" in the repository
	// post: in the repository, the event with id "id" has the same contents as "newEvent"
	virtual void update(int id, Event newEvent);

	virtual void incrementAttendance(int eventId);
	virtual void decrementAttendance(int eventId);

	friend void testEventRepository();
};
