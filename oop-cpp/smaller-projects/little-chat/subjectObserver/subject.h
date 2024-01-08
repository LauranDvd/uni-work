#pragma once
#include <vector>
#include "observer.h"

class Subject {
private:
	std::vector<Observer*> allObservers;

public:
	void registerObserver(Observer* observer);
	void unregisterObserver(Observer* observer);
	void notify();
};