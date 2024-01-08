#include <QMessageBox>
#include <qspinbox.h>
#include "userWindow.h"
#include <windows.h>
#include <shellapi.h>

UserWindow::UserWindow(UserService& service, QWidget* parent) : QMainWindow{parent}, service{service} {
	ui.setupUi(this);

	populateList();
	updateParsersMonth();
	connectSignalsAndSlots();
}

void UserWindow::dislikeSelectedEvent() {
	int selectedIndex = getSelectedIndex();
	if (selectedIndex == -1) {
		QMessageBox::critical(this, "Problem", "Select sth");
		return;
	}

	auto allInShortlist = service.getEventsInShortlist();
	service.deleteShortlist(allInShortlist[selectedIndex].getId());

	populateList();
}

void UserWindow::connectSignalsAndSlots() {
	QObject::connect(ui.dislikeButton, &QPushButton::clicked, this, &UserWindow::dislikeSelectedEvent);
	QObject::connect(ui.parserNext, &QPushButton::clicked, this, &UserWindow::parserShowNext);
	QObject::connect(ui.parserLike, &QPushButton::clicked, this, &UserWindow::parserLike);
	QObject::connect(ui.openLinkButton, &QPushButton::clicked, this, &UserWindow::openLinkOfSelected);
	QObject::connect(ui.openListExternallyButton, &QPushButton::clicked, this, &UserWindow::openListExternally);

	QObject::connect(ui.monthInput, &QSpinBox::valueChanged, this, &UserWindow::updateParsersMonth);
}

void UserWindow::populateList() {
	ui.allEventsList->clear();
	auto allItems = service.getEventsInShortlist();
	for (auto item : allItems)
		ui.allEventsList->addItem(QString::fromStdString(item.toString()));
}

void UserWindow::updateParsersMonth() {
	int month = ui.monthInput->value();
	auto allEventsInThatMonth = service.getAllEventsInMonth(month);
	if (allEventsInThatMonth.size() == 0)
		ui.eventsParserText->setText("No events in that month");
	else {
		parserIndex = 0;
		ui.eventsParserText->setText(QString::fromStdString(allEventsInThatMonth[parserIndex].toString()));
	}
}

void UserWindow::parserShowNext() { 
	int month = ui.monthInput->value();
	auto allEventsInThatMonth = service.getAllEventsInMonth(month);
	if (allEventsInThatMonth.size() == 0)
		ui.eventsParserText->setText("No events in that month");
	else {
		parserIndex = (parserIndex + 1) % allEventsInThatMonth.size();
		ui.eventsParserText->setText(QString::fromStdString(allEventsInThatMonth[parserIndex].toString()));
	}
}

void UserWindow::parserLike() {
	int month = ui.monthInput->value();
	auto allEventsInThatMonth = service.getAllEventsInMonth(month);

	if (allEventsInThatMonth.size() == 0) {
		QMessageBox::critical(this, "Problem", "Nothing to like");
		return;
	}

	int idOfEventDisplayed = allEventsInThatMonth[parserIndex].getId();
	try {
		service.addShortlist(idOfEventDisplayed);
	}
	catch (std::exception& caught) {  // event already in shortlist
		QMessageBox::critical(this, "Error", caught.what());
	}
	populateList();
}

void UserWindow::openLinkOfSelected() {
	int selectedIndex = getSelectedIndex();
	if (selectedIndex == -1) {
		QMessageBox::critical(this, "Problem", "Select sth");
		return;
	}

	char command[100] = "start ";
	strcat(command, service.getEventsInShortlist()[selectedIndex].getLink().c_str());
	system(command);
}

void UserWindow::openListExternally() {
	service.seeShortlistExtern();
}

int UserWindow::getSelectedIndex() {
	auto selected = ui.allEventsList->selectionModel()->selectedIndexes();
	if (selected.size() == 0)
		return -1;
	return selected.at(0).row();
}
