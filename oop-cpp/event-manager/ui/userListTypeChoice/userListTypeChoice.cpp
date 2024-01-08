#include "userListTypeChoice.h"
#include "txtEventRepository.h"
#include "htmlShortlist.h"
#include "userWindow.h"
#include "adminWindow.h"
#include "csvShortlist.h"

UserListTypeChoice::UserListTypeChoice(QWidget* parent) : QWidget{ parent } {
	ui.setupUi(this);

	connectSignalsAndSlots();
}

void UserListTypeChoice::startupHTML() {
	TxtEventRepository* repository = new TxtEventRepository{ "data.txt" };
	HTMLShortlist* shortlist = new HTMLShortlist{ *repository, "myList.html" };
	UserService* service = new UserService{ repository, shortlist };
	UserWindow* userWindow = new UserWindow{ *service };
	userWindow->show();

	hide();
}

void UserListTypeChoice::startupCSV() {
	TxtEventRepository* repository = new TxtEventRepository{ "data.txt" };
	CSVShortlist* shortlist = new CSVShortlist{ *repository, "myList.csv" };
	UserService* service = new UserService{ repository, shortlist };
	UserWindow* userWindow = new UserWindow{ *service };
	userWindow->show();

	hide();
}

void UserListTypeChoice::connectSignalsAndSlots() {
	QObject::connect(ui.htmlButton, &QPushButton::clicked, this, &UserListTypeChoice::startupHTML);
	QObject::connect(ui.csvButton, &QPushButton::clicked, this, &UserListTypeChoice::startupCSV);
}
