#include "txtEventRepository.h"
#include <fstream>
#include <iostream>


TxtEventRepository::TxtEventRepository(std::string _filename) : FileEventRepository(_filename) {
	loadFromFile();
}

void TxtEventRepository::loadFromFile() {
	std::ifstream repositoryStream(this->filename);
	std::string uselessLine;

	Event gathering;
	repositoryStream >> gathering;
	while (!repositoryStream.eof()) {
		nextId = std::max(nextId, gathering.getId() + 1);
		this->events.push_back(gathering);

		getline(repositoryStream, uselessLine);
		if (!repositoryStream.eof())
			repositoryStream >> gathering;
	}

	repositoryStream.close();
}

void TxtEventRepository::writeToFile() const {
	std::ofstream repositoryStream(this->filename);

	for (Event gathering : events)
		repositoryStream << gathering << "\n\n";

	repositoryStream.close();
}
