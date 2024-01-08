#include "fileEventRepository.h"


void FileEventRepository::add(Event gathering) {
	EventRepository::add(gathering);
	writeToFile();
}

void FileEventRepository::remove(const Event& gathering) {
	EventRepository::remove(gathering);
	writeToFile();
}

void FileEventRepository::update(int id, Event newEvent) {
	EventRepository::update(id, newEvent);
	writeToFile();
}

void FileEventRepository::incrementAttendance(int eventId) {
	EventRepository::incrementAttendance(eventId);
	writeToFile();
}

void FileEventRepository::decrementAttendance(int eventId) {
	EventRepository::decrementAttendance(eventId);
	writeToFile();
}
