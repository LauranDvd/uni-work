#pragma once
#include <string>
#include <ostream>

class Event {
private:
	std::string title;
	std::string description;
	std::string timeDate, timeHour;
	int numberOfPeopleAttending;
	std::string socialMediaLink;
	int id;

public:
	Event();
	Event(std::string title, std::string description, std::string timeDate, std::string timeHour, int numberOfPeopleAttending, std::string socialMediaLink, int id);

	bool operator==(const Event& gathering) const;

	friend std::ostream& operator<<(std::ostream& outputStream, Event& gathering);
	friend std::istream& operator>>(std::istream& inputStream, Event& gathering);

	void setId(int id);
	void setAttendance(int newAttendance);
	int getId() const;
	int getMonth() const;
	std::string getDate() const;
	std::string getHour() const;
	std::string getLink() const;
	std::string getTitle() const {
		return title;
	}
	std::string getDescription() const {
		return description;
	}
	int getAttendance() const;

	// compares everything, except the id
	bool hasSameFieldsMaybeExceptId(Event other) const;

	std::string toString() const;
	std::string toCSVForm() const;
	std::string toHTMLRowForm() const;

	friend void testEvent();
};
