#pragma once
#include "eventRepository.h"
#include <vector>

class Shortlist {
protected:
	EventRepository& repository;
	std::vector<int> idsInList;

public:
	Shortlist(EventRepository& _repository) : repository{ _repository } {}
	virtual ~Shortlist() {}

	virtual std::vector<int> getAllIds() const;
	virtual void addEventId(int idToAdd);
	virtual void removeEventId(int idToRemove);
};