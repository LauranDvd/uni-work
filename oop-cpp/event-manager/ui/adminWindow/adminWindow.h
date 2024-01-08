#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_adminWindow.h"
#include "adminService.h"

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    AdminWindow(AdminService& service, QWidget* parent = nullptr);
    ~AdminWindow();

private:
    AdminService& service;
    Ui::AdminWindowClass ui;

    void connectSignalsAndSlots();
    
    void populateList();

    void addEvent();
    void updateEvent();
    int getSelectedIndex();
    void openChart();

public slots:
    void deleteEvent();
};
