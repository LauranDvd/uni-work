#pragma once
#include "eventValidator.h"

class FakeEventValidator : public EventValidator {
public:
	bool alwaysThrowsOrNeverThrows;

	void validate(const Event& gathering) override {
		if (alwaysThrowsOrNeverThrows)
			throw(EventException(std::vector<std::string>(0)));
	}
};