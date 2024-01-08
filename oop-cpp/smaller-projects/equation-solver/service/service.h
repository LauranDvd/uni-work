#pragma once
#include "repository.h"

class Service {
private:
	Repository* repository;

public:
	Service(Repository* repository) : repository{ repository } {}

	std::vector<Equation> getAll() const;

	// "index" being the index in getAll()
	void updateByIndex(int index, int newA, int newB, int newC);

	std::pair<std::string, std::string> getSolutions(int index) const;
};