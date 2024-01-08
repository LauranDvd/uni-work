#include "csvShortlist.h"
#include <algorithm>
#include <fstream>

void CSVShortlist::saveToFile() {
	std::vector<Event> eventsInList;
	for_each(idsInList.begin(), idsInList.end(), [&eventsInList, this](const int oneId) {
		eventsInList.push_back(repository.findById(oneId));
		});

	std::ofstream writeStream(filename);

	for_each(eventsInList.begin(), eventsInList.end(), [&writeStream](const Event& gathering) {
		writeStream << gathering.toCSVForm() << "\n";
		});

	writeStream.close();
}
