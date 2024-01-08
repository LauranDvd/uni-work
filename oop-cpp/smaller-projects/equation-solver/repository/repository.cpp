#include "repository.h"

void Repository::updateByCoefficients(int currentA, int currentB, int currentC, int newA, int newB, int newC) {
	for (Equation& equation: allEquations)
		if (equation.getA() == currentA && equation.getB() == currentB && equation.getC() == currentC) {
			equation = Equation{ newA, newB, newC };
		}

}
