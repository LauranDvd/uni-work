#include "equation.h"
#include <string>
#include <sstream>

double Equation::getDelta() const {
	return 1.00 * b * b - 4.00 * a * c;
}

bool Equation::hasRealSolution() const {
	return getDelta() >= 0;
}

std::string Equation::toString() const {
	std::stringstream stringForm;

	stringForm << a << "x^2 + " << b << "x + " << c << "=0";

	return stringForm.str();
}
