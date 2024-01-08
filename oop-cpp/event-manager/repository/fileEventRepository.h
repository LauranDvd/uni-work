#pragma once
#include <string>
#include "eventRepository.h"

class FileEventRepository : public EventRepository {
protected:
	std::string filename;

public:
	FileEventRepository(std::string _filename) : filename{ _filename } {};
	virtual ~FileEventRepository() override {}

	void add(Event gathering) override;
	void remove(const Event& gathering) override;
	void update(int id, Event newEvent) override;
	void incrementAttendance(int eventId) override;
	void decrementAttendance(int eventId) override;

	virtual void loadFromFile() = 0;
	virtual void writeToFile() const = 0;
};