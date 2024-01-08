#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_equationsGUI.h"
#include "service.h"

class equationsGUI : public QMainWindow
{
    Q_OBJECT

public:
    equationsGUI(Service* service, QWidget* parent = nullptr);
    ~equationsGUI();

private:
    Ui::equationsGUIClass ui;
    Service* service;

    void connectSignalsAndSlots();
    void populateList();
    int getSelectedIndex() const;

public:
    void updateEquation();
    void computeSolutions();
};
