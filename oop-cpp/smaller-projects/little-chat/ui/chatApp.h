#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_chatApp.h"
#include "chatSession.h"
#include "observer.h"

class chatApp : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    chatApp(ChatSession* session, User* user, QWidget *parent = nullptr);
    ~chatApp();
    void update() override;
    void sendMessage();

private:
    Ui::chatAppClass ui;
    ChatSession* session;
    User* user;

    void connectSignalsAndSlots();
};
