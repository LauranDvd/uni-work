#include <vector>
#include "shortlist.h"
#include "idNotFoundInShortlistException.h"
#include "duplicateEventException.h"

std::vector<int> Shortlist::getAllIds() const {
	return idsInList;
}

void Shortlist::addEventId(int idToAdd) {
	if (find(idsInList.begin(), idsInList.end(), idToAdd) != idsInList.end())
		throw std::exception("Already in your shortlist");

	idsInList.push_back(idToAdd);
}

void Shortlist::removeEventId(int idToRemove) {
	if (find(idsInList.begin(), idsInList.end(), idToRemove) == idsInList.end())
		throw(IDNotFoundInShortlistException());

	idsInList.erase(std::remove(idsInList.begin(), idsInList.end(), idToRemove), idsInList.end());
}