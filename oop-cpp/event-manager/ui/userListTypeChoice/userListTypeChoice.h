#pragma once
#include <qwidget.h>
#include "ui_userListTypeChoice.h"

class UserListTypeChoice : public QWidget {
    Q_OBJECT

public:
    UserListTypeChoice(QWidget* parent = nullptr);
    ~UserListTypeChoice() {};
    void startupHTML();
    void startupCSV();

private:
    Ui::UserListTypeChoiceWidget ui;

    void connectSignalsAndSlots();
};