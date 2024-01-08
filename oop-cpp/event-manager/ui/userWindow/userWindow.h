#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_userWindow.h"
#include "userService.h"

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    UserWindow(UserService& service, QWidget* parent = nullptr);
    ~UserWindow() {};

    void dislikeSelectedEvent();
    void parserLike();
    void openLinkOfSelected();
    void openListExternally();

private:
    UserService& service;
    Ui::UserWindow ui;
    int parserIndex;

    void connectSignalsAndSlots();
    void populateList();
    void updateParsersMonth();
    void parserShowNext();
    int getSelectedIndex();
};
