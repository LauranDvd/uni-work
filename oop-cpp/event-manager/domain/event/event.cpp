#define _CRT_SECURE_NO_WARNINGS
#include "event.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Event::operator==(const Event& gathering) const {
	return this->id == gathering.getId();
}

std::ostream& operator<<(std::ostream& outputStream, Event& gathering) {
	outputStream << gathering.toString();
	return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Event& gathering) {
	char bufferForStrings[300], secondBufferForStrings[300];
	std::string uselessLine;
	
	std::string firstLine;
	getline(inputStream, uselessLine); getline(inputStream, firstLine);
	if (inputStream.eof())
		return inputStream;
	sscanf(firstLine.c_str(), "%d. %[^|]| %d people attending", &gathering.id, bufferForStrings, &gathering.numberOfPeopleAttending);
	bufferForStrings[strlen(bufferForStrings) - 1] = 0;  // we read an extra space, remove it
	gathering.title = bufferForStrings;

	std::string secondLine;
	getline(inputStream, secondLine);
	sscanf(secondLine.c_str(), "%s at %s", bufferForStrings, secondBufferForStrings);
	gathering.timeDate = bufferForStrings;
	gathering.timeHour = secondBufferForStrings;

	getline(inputStream, gathering.socialMediaLink);
	getline(inputStream, uselessLine);
	getline(inputStream, gathering.description);

	getline(inputStream, uselessLine);  // ---
	getline(inputStream, uselessLine);  // empty line

	return inputStream;
}

Event::Event() : title(""), description(""), numberOfPeopleAttending(0), socialMediaLink(""), timeDate("1970.01.01"), timeHour("12:00"), id(0) {};

Event::Event(std::string title, std::string description, std::string timeDate, std::string timeHour, int numberOfPeopleAttending, std::string socialMediaLink, int id) {
	this->id = id;
	this->title = title;
	this->description = description;
	this->timeDate = timeDate;
	this->timeHour = timeHour;
	this->numberOfPeopleAttending = numberOfPeopleAttending;
	this->socialMediaLink = socialMediaLink;
}

std::string Event::toString() const {
	std::stringstream representation;
	representation << "--------------------------------------------------\n";
	representation << id << ". ";
	representation << title << " | " << numberOfPeopleAttending << " people attending\n";
	representation << timeDate << " at " << timeHour << "\n";
	representation << socialMediaLink << "\n";
	representation << "-----\n";
	representation << description << "\n";
	representation << "--------------------------------------------------\n";
	return representation.str();
}

std::string Event::toCSVForm() const {
	std::stringstream representation;

	representation << title << "," << timeDate << "," << timeHour << "," << numberOfPeopleAttending <<
		"," << socialMediaLink << "," << description;

	return representation.str();
}

std::string Event::toHTMLRowForm() const {
	std::stringstream toReturn;
	toReturn << "<tr>\n";
	toReturn << "<td>" << title << "</td>\n";
	toReturn << "<td>" << timeDate << "</td>\n";
	toReturn << "<td>" << timeHour << "</td>\n";
	toReturn << "<td>" << numberOfPeopleAttending << "</td>\n";
	toReturn << "<td>" << socialMediaLink << "</td>\n";
	toReturn << "<td>" << description << "</td>\n";
	toReturn << "</tr>\n";
	return toReturn.str();
}

int Event::getId() const {
	return id;
}

void Event::setId(int id) {
	this->id = id;
}

void Event::setAttendance(int newAttendance) {
	numberOfPeopleAttending = newAttendance;
}

int Event::getMonth() const {
	// timeDate has format 2012.05.12
	std::string monthString = timeDate.substr(5, 2);
	return 10 * (monthString[0] - '0') + (monthString[1] - '0');
}

std::string Event::getDate() const {
	return timeDate;
}

std::string Event::getHour() const {
	return timeHour;
}

std::string Event::getLink() const {
	return socialMediaLink;
}

int Event::getAttendance() const {
	return numberOfPeopleAttending;
}

bool Event::hasSameFieldsMaybeExceptId(Event other) const {
	return title == other.title && timeDate == other.timeDate && timeHour == other.timeHour &&
		numberOfPeopleAttending == other.numberOfPeopleAttending && description == other.description &&
		socialMediaLink == other.socialMediaLink;
}
