#pragma once
#include "eventRepository.h"

class MemoryEventRepository : public EventRepository {
public:
	MemoryEventRepository() noexcept : EventRepository{} {}
	MemoryEventRepository(const MemoryEventRepository& repository);

	~MemoryEventRepository() override {}
};
