#include "chatApp.h"
#include <qmessagebox.h>

chatApp::chatApp(ChatSession* session, User* user, QWidget *parent)
    : QMainWindow(parent), session{session}, user{user}
{
    ui.setupUi(this);
    setWindowTitle(QString::fromStdString(user->getName()));
    session->registerObserver(this);

    connectSignalsAndSlots();
}

chatApp::~chatApp()
{}

void chatApp::update() {
    auto allMessages = session->getMessages();
    ui.allMessagesList->clear();
    for (auto message : allMessages) {
        std::string whatWrite = message.getUser().getUniqueUserName() + ": " + message.getMessage();
        ui.allMessagesList->addItem(QString::fromStdString(whatWrite));
    }
}

void chatApp::sendMessage() {
    std::string message = ui.messageInput->text().toStdString();
    session->addMessage(*user, message);
}

void chatApp::connectSignalsAndSlots() {
    QObject::connect(ui.sendButton, &QPushButton::clicked, this, &chatApp::sendMessage);
}
