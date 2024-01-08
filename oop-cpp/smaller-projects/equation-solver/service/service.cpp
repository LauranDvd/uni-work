#include "service.h"
#include <QString>
#include <string>

std::vector<Equation> Service::getAll() const {
	return repository->getAll();
}

void Service::updateByIndex(int index, int newA, int newB, int newC) {
	Equation toBeUpdated = repository->getAll()[index];

	repository->updateByCoefficients(toBeUpdated.getA(), toBeUpdated.getB(), toBeUpdated.getC(), newA, newB, newC);
}

std::pair<std::string, std::string> Service::getSolutions(int index) const {
	Equation toBeSolved = repository->getAll()[index];
	int a = toBeSolved.getA(), b = toBeSolved.getB(), c = toBeSolved.getC();
	double delta = toBeSolved.getDelta();
	
	if (delta >= 0) {
		double firstSolution = (-b - sqrt(delta)) / (2 * a);
		double secondSolution = (-b + sqrt(delta)) / (2 * a);

		return make_pair(std::to_string(firstSolution), std::to_string(secondSolution));
	}
	else {
		double firstSolution = (-b - sqrt(-delta)) / (2 * a);
		double secondSolution = (-b + sqrt(-delta)) / (2 * a);

		double realPart = 1.00 * (-b) / (2 * a);
		double imaginaryPart = 1.00 * sqrt(-delta) / (2 * a);

		return make_pair(std::to_string(realPart) + "+" + std::to_string(imaginaryPart) + "i", 
			std::to_string(realPart) + "-" + std::to_string(imaginaryPart) + "i");
	}

}
