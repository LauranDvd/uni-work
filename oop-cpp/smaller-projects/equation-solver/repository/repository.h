#pragma once
#include <vector>
#include "equation.h"

class Repository {
protected:
	std::vector<Equation> allEquations;

public:
	std::vector<Equation> getAll() const { return allEquations; }

	void updateByCoefficients(int currentA, int currentB, int currentC, int newA, int newB, int newC);
};