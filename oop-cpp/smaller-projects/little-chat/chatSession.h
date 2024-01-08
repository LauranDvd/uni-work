#pragma once
#include <string>
#include "user.h"
#include <vector>
#include "userMessage.h"
#include "subject.h"

class ChatSession : public Subject {
private:
	std::vector<UserMessage> messages;
public:
	void addMessage(User user, std::string message);
	std::vector<UserMessage> getMessages() const;
};