#pragma once
#include "fileShortlist.h"

class HTMLShortlist : public FileShortlist {
public:
	HTMLShortlist(EventRepository& _repository, std::string _filename) : FileShortlist{ _repository, _filename } { saveToFile(); }
	~HTMLShortlist() override {}

	void saveToFile() override;
};