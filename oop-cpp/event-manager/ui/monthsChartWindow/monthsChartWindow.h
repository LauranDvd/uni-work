#pragma once
#include <qwidget.h>
#include "ui_monthsChartWindow.h"
#include "adminService.h"

class MonthsChartWindow : public QWidget {
    Q_OBJECT

public:
    MonthsChartWindow(AdminService* service, QWidget* parent = nullptr);
    ~MonthsChartWindow();

private:
    Ui::MonthsChartWidget ui;
    AdminService* service;

private:
    void makeThePlot();
};