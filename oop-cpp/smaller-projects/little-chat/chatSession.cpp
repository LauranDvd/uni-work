#include "chatSession.h"
#include "qdebug.h"

void ChatSession::addMessage(User user, std::string message) {
	qDebug() << "adding message...";
	messages.push_back(UserMessage{ message, user });
	notify();
}

std::vector<UserMessage> ChatSession::getMessages() const {
	return messages;
}
