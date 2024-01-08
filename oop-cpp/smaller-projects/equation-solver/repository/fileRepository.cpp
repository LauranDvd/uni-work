#include "fileRepository.h"
#include <fstream>
#include <string>

void FileRepository::loadFromFile() {
	std::ifstream inputFile(filename);

	std::string a, b, c;
	while (inputFile >> a >> b >> c) {
		a = a.substr(0, a.size() - 1);
		b = b.substr(0, b.size() - 1);
		allEquations.push_back(Equation{ atoi(a.c_str()), atoi(b.c_str()), atoi(c.c_str()) });
	}

	inputFile.close();
}
