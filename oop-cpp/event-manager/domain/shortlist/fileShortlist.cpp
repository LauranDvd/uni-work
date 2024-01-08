#include "fileShortlist.h"
#include "idNotFoundInShortlistException.h"

std::string FileShortlist::getFilename() const {
	return filename;
}

void FileShortlist::addEventId(int idToAdd) {
	Shortlist::addEventId(idToAdd);
	saveToFile();
}

void FileShortlist::removeEventId(int idToRemove) {
	Shortlist::removeEventId(idToRemove);
	saveToFile();  
}

// should work with most types of files
void FileShortlist::openExtern() const {
	system(("START " + filename).c_str());
}
