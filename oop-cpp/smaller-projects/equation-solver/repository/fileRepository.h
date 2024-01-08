#pragma once
#include "repository.h"
#include <string>

class FileRepository : public Repository {
private:
	std::string filename;

public:
	FileRepository(std::string filename) : Repository{}, filename{ filename } { loadFromFile(); }

private:
	void loadFromFile();
};