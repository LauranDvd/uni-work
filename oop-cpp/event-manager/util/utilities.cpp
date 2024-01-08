#include <string>
#include <iostream>
#include "utilities.h"

// returns -1 if "given" is not a positive integer
int stringToInt(std::string given) {
	int obtained = 0;
	for (char charInGiven : given)
		if (!('0' <= charInGiven && charInGiven <= '9'))
			return -1;
		else
			obtained = obtained * 10 + (charInGiven - '0');
	return obtained;
}

int readIntGracefully() {
	std::string read;
	std::cin >> read;
	while (!isInt(read)) {
		std::cout << "ERROR: Not a number\n>";
		std::cin >> read;
	}
	return stringToInt(read);
}

bool isInt(std::string putOnTrial) {
	return find_if(putOnTrial.begin(), putOnTrial.end(), [](const char charInIt) {
		return !('0' <= charInIt && charInIt <= '9');
		}) == putOnTrial.end();
}

std::string qtDateToDisciplinateDate(std::string qtForm) {
	std::string year = qtForm.substr(qtForm.size() - 4, 4);
	
	int monthLeftIndex = 0, monthRightIndex = qtForm.size() - 6;  // "right" is on the day
	while (qtForm[monthLeftIndex] != ' ')
		monthLeftIndex++;
	monthLeftIndex++;
	while (qtForm[monthRightIndex] != ' ')
		monthRightIndex--;
	monthRightIndex--;
	std::string monthInLetters = qtForm.substr(monthLeftIndex, monthRightIndex - monthLeftIndex + 1);
	std::string month = monthFromLettersToNumberForm(monthInLetters);
	if (month.size() < 2)
		month = "0" + month;

	int dayLeftIndex = monthRightIndex + 2, dayRightIndex = qtForm.size() - 6;
	std::string day = qtForm.substr(dayLeftIndex, dayRightIndex - dayLeftIndex + 1);
	if (day.size() < 2)
		day = "0" + day;

	return year + "." + month + "." + day;
}

std::string monthFromLettersToNumberForm(std::string inLetters) {
	if (inLetters == "Jan")
		return "1";
	else if (inLetters == "Feb")
		return "2";
	else if (inLetters == "Mar")
		return "3";
	else if (inLetters == "Apr")
		return "4";
	else if (inLetters == "May")
		return "5";
	else if (inLetters == "Jun")
		return "6";
	else if (inLetters == "Jul")
		return "7";
	else if (inLetters == "Aug")
		return "8";
	else if (inLetters == "Sep")
		return "9";
	else if (inLetters == "Oct")
		return "10";
	else if (inLetters == "Nov")
		return "11";
	else
		return "12";
}

std::string monthFromIntToString(int month) {
	switch (month) {
		case 1: return "Jan";
		case 2: return "Feb";
		case 3: return "Mar";
		case 4: return "Apr";
		case 5: return "May";
		case 6: return "Jun";
		case 7: return "Jul";
		case 8: return "Aug";
		case 9: return "Sep";
		case 10: return "Oct";
		case 11: return "Nov";
		case 12: return "Dec";
	}
}

std::string randomColorString() {
	srand(time(NULL));
	int random = rand() % 5;
	switch (random) {
		case 0: return "red";
		case 1: return "orange";
		case 2: return "yellow";
		case 3: return "pink";
		case 4: return "gray";
	}
}
