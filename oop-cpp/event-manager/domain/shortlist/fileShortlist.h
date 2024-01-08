#pragma once
#include "eventRepository.h"
#include "shortlist.h"

class FileShortlist : public Shortlist {
protected:
	std::string filename;

public:
	FileShortlist(EventRepository& _repository, std::string _filename) : Shortlist{_repository}, filename{_filename} {};
	virtual ~FileShortlist() {}

	virtual void saveToFile() = 0;
	std::string getFilename() const;

	void addEventId(int idToAdd) override;
	void removeEventId(int idToRemove) override;

	virtual void openExtern() const;
};