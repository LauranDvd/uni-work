#pragma once
#include "fileEventRepository.h"

class TxtEventRepository : public FileEventRepository {
public:
	TxtEventRepository(std::string _filename);
	~TxtEventRepository() override {};

	void loadFromFile() override;
	void writeToFile() const override;
};