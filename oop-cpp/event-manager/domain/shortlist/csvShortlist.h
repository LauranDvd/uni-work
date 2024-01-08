#pragma once
#include "fileShortlist.h"

class CSVShortlist : public FileShortlist {
public:
	CSVShortlist(EventRepository& _repository, std::string _filename) : FileShortlist{ _repository, _filename } { saveToFile(); }
	~CSVShortlist() override {}

	void saveToFile() override;
};