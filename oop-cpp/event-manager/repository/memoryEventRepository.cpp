#include "memoryEventRepository.h"

MemoryEventRepository::MemoryEventRepository(const MemoryEventRepository& repository) {
	this->events = repository.events;
}
