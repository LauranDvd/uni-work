#include "event.h"
#include "eventRepository.h"
#include <iostream>
#include "duplicateEventException.h"


EventRepository::EventRepository(const EventRepository& repository) {
	this->events = repository.events;
}

// it searches based on the content of the events (everything except the id)
bool EventRepository::existsEvent(Event& gathering) const {
	return std::find_if(events.begin(), events.end(), [gathering](const Event gatheringInEvents) {
		return gathering.hasSameFieldsMaybeExceptId(gatheringInEvents);
		}) != events.end();
}

void EventRepository::add(Event gathering) {
	if (existsEvent(gathering)) {
		throw(DuplicateEventException());
	}

	nextId++;
	gathering.setId(nextId);

	this->events.push_back(gathering);
}

void EventRepository::remove(const Event& gathering) {
	events.erase(std::remove(events.begin(), events.end(), gathering), events.end());
}

std::vector<Event> EventRepository::getAll() const {
	return std::vector<Event>(events);
}

// assumes the id exists
Event EventRepository::findById(int id) const {
	return *std::find_if(events.begin(), events.end(), [id](const Event gatheringInEvents) {
		return id == gatheringInEvents.getId();
		});
}

bool EventRepository::existsId(int id) const {
	return std::find_if(events.begin(), events.end(), [id](const Event gatheringInEvents) {
		return id == gatheringInEvents.getId();
		}) != events.end();
}

void EventRepository::update(int id, Event newEvent) {
	newEvent.setId(id);

	Event& soughtEvent = *std::find_if(events.begin(), events.end(), [id](const Event gatheringInEvents) {
		return id == gatheringInEvents.getId();
		});
	soughtEvent = newEvent;
}

void EventRepository::incrementAttendance(int eventId) {
	Event& soughtEvent = *std::find_if(events.begin(), events.end(), [eventId](const Event gatheringInEvents) {
		return eventId == gatheringInEvents.getId();
		});
	soughtEvent.setAttendance(soughtEvent.getAttendance() + 1);
}

void EventRepository::decrementAttendance(int eventId) {
	Event& soughtEvent = *std::find_if(events.begin(), events.end(), [eventId](const Event gatheringInEvents) {
		return eventId == gatheringInEvents.getId();
		});
	soughtEvent.setAttendance(soughtEvent.getAttendance() - 1);
}
