#include "startupModeChoice.h"
#include "txtEventRepository.h"
#include "adminService.h"
#include "adminWindow.h"
#include "userWindow.h"
#include "userService.h"
#include "htmlShortlist.h"
#include "userListTypeChoice.h"

StartupModeChoice::StartupModeChoice(QWidget* parent) : QWidget{parent} {
	ui.setupUi(this);

	connectSignalsAndSlots();
}

void StartupModeChoice::connectSignalsAndSlots() {
	QObject::connect(ui.adminModeChoice, &QPushButton::clicked, this, &StartupModeChoice::startupAdmin);
	QObject::connect(ui.userModeChoice, &QPushButton::clicked, this, &StartupModeChoice::startupUser);
}

void StartupModeChoice::startupAdmin() {
	TxtEventRepository* repository = new TxtEventRepository{ "data.txt" };
    AdminService* service = new AdminService{ repository };
    AdminWindow* w = new AdminWindow{ *service };  // TODO refactor "reretry" into "AdminWindow"
    w->show();

	hide();
}

void StartupModeChoice::startupUser() {
	UserListTypeChoice* listTypeChoiceWindow = new UserListTypeChoice;
	listTypeChoiceWindow->show();

	hide();
}
