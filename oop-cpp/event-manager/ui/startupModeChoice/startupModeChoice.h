#pragma once
#include <qwidget.h>
#include "ui_startupModeChoice.h"

class StartupModeChoice : public QWidget {
    Q_OBJECT

public:
    StartupModeChoice(QWidget* parent = nullptr);
    ~StartupModeChoice() {};

private:
    Ui::ModeChoiceWindow ui;

    void connectSignalsAndSlots();
    void startupAdmin();
    void startupUser();
};