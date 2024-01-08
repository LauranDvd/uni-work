#pragma once
#include "shortlistException.h"

class IDNotFoundInShortlistException : public ShortlistException {
public:
	IDNotFoundInShortlistException() : ShortlistException{ "The event with that ID is not in your shortlist." } {};
	~IDNotFoundInShortlistException() override {}

	//const char* what() override { return message.c_str(); }
};