#include "adminWindow.h"
#include "event.h"
#include "utilities.h"
#include <QMessageBox>
#include <QDebug>
#include "duplicateEventException.h"
#include "monthsChartWindow.h"

AdminWindow::AdminWindow(AdminService& service, QWidget *parent)
    : QMainWindow(parent), service{service}
{
    ui.setupUi(this);
	populateList();
	connectSignalsAndSlots();
}

AdminWindow::~AdminWindow()
{}

void AdminWindow::connectSignalsAndSlots() {
	QObject::connect(ui.addButton, &QPushButton::clicked, this, &AdminWindow::addEvent);
	QObject::connect(ui.updateButton, &QPushButton::clicked, this, &AdminWindow::updateEvent);
	QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &AdminWindow::deleteEvent);
	QObject::connect(ui.openChart, &QPushButton::clicked, this, &AdminWindow::openChart);
}

void AdminWindow::populateList() {
	ui.allEventsListWidget->clear();
	for (Event gathering : service.getAll())
		ui.allEventsListWidget->addItem(QString::fromStdString(gathering.toString()));
}

void AdminWindow::addEvent() {
	std::string title = ui.titleInput->text().toStdString();
	std::string description = ui.descriptionInput->toPlainText().toStdString();
	std::string timeDate = ui.dateHourInput->date().toString().toStdString();
	std::string timeHour = ui.dateHourInput->time().toString().toStdString();
	int numberOfPeopleAttending = ui.attendanceInput->text().toInt();
	std::string socialMediaLink = ui.linkInput->text().toStdString();

	timeDate = qtDateToDisciplinateDate(timeDate);
	timeHour = timeHour.substr(0, 5);

	try {
		this->service.add(title, description, timeDate, timeHour, numberOfPeopleAttending, socialMediaLink);
	}
	catch (EventException& caught) {
		for (std::string problem : caught.getProblems())
			QMessageBox::critical(this, "ERROR: ", QString::fromStdString(problem));
	}
	catch (DuplicateEventException& caught) {
		QMessageBox::critical(this, "ERROR: ", QString::fromStdString(caught.what()));
	}
	populateList();
}

void AdminWindow::updateEvent() {
	std::string title = ui.titleInput->text().toStdString();
	std::string description = ui.descriptionInput->toPlainText().toStdString();
	std::string timeDate = ui.dateHourInput->date().toString().toStdString();
	std::string timeHour = ui.dateHourInput->time().toString().toStdString();
	int numberOfPeopleAttending = ui.attendanceInput->text().toInt();
	std::string socialMediaLink = ui.linkInput->text().toStdString();

	timeDate = qtDateToDisciplinateDate(timeDate);
	timeHour = timeHour.substr(0, 5);

	if (getSelectedIndex() == -1) {
		QMessageBox::critical(this, "ERROR", "Nothing selected");
		return;
	}
	int idSelected = service.getAll()[getSelectedIndex()].getId();

	try {
		this->service.update(idSelected, title, description, timeDate, timeHour, numberOfPeopleAttending, socialMediaLink);
	}
	catch (EventException& caught) {
		for (std::string problem : caught.getProblems())
			QMessageBox::critical(this, "ERROR: ", QString::fromStdString(problem));
	}
	populateList();
}

int AdminWindow::getSelectedIndex() {
	auto indexes = ui.allEventsListWidget->selectionModel()->selectedIndexes();
	if (indexes.count() == 0)
		return -1;
	return indexes[0].row();
}

void AdminWindow::openChart() {
	MonthsChartWindow* chartWindow = new MonthsChartWindow{ &service };
	chartWindow->show();
}

void AdminWindow::deleteEvent() {
	int rowSelected = getSelectedIndex();
	if (rowSelected == -1) {
		QMessageBox::critical(this, "ERROR", "Nothing selected");
		return;
	}
	service.removeById(service.getAll()[rowSelected].getId());  // assuming service.getAll() gives the same order listwidget's
	populateList();
}
