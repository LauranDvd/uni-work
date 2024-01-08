#pragma once
#include "eventRepositoryException.h"

class DuplicateEventException : public EventRepositoryException {
public:
	DuplicateEventException() : EventRepositoryException{ "Such an event already exists." } {};
	~DuplicateEventException() override {}

	//const char* what() override { return message.c_str(); }
};