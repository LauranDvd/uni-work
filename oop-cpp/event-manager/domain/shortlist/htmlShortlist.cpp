#include "htmlShortlist.h"
#include <algorithm>
#include <fstream>

void HTMLShortlist::saveToFile() {
	std::vector<Event> eventsInList;
	for_each(idsInList.begin(), idsInList.end(), [&eventsInList, this](const int oneId) {
		eventsInList.push_back(repository.findById(oneId));
		});

	std::ofstream writeStream(filename);

	std::string toBeWrittenBeforeTheEvents = "\
<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>Shortlist</title>\n\
</head>\n\
<body>\n\
<table border = \"1\">\n\
<tr>\
<td>Event name</td>\
<td>Date</td>\
<td>Hour</td>\
<td>Attendance</td>\
<td>Site</td>\
<td>Description</td>\
</tr>";

	std::string toBeWrittenAfterTheEvents = "\
</table>\n\
</body>\n\
</html>\n";

	writeStream << toBeWrittenBeforeTheEvents;

	for_each(eventsInList.begin(), eventsInList.end(), [&writeStream](const Event& gathering) {
		writeStream << gathering.toHTMLRowForm() << "\n";
		});

	writeStream << toBeWrittenAfterTheEvents;

	writeStream.close();
}
