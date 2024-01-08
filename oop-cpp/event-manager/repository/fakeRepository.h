#pragma once
#include "eventRepository.h"

class FakeRepository : public EventRepository {
public:
	bool returnsSomethingAtGetAll;
	int monthToReturnTwoOfAtGetAll;
	int monthToReturnOneOfAtGetAll;

	FakeRepository() : EventRepository{}, returnsSomethingAtGetAll { false }, monthToReturnTwoOfAtGetAll{ -1 }, monthToReturnOneOfAtGetAll{ -1 } {};

	std::vector<Event> getAll() const override;
};