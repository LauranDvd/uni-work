#include "chatApp.h"
#include <QtWidgets/QApplication>
#include "chatSession.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    ChatSession session{};

    User david{ "david", "David Thompson" };
    chatApp davidWindow{ &session, &david };
    User cristi{ "cris", "Cristian Rodriguez" };
    chatApp cristiWindow{ &session , &cristi };

    davidWindow.show();
    cristiWindow.show();

    return a.exec();
}
