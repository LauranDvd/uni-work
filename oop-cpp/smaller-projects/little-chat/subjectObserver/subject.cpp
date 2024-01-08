#include "subject.h"
#include "qdebug.h"

void Subject::registerObserver(Observer* observer) {
	allObservers.push_back(observer);
}

void Subject::unregisterObserver(Observer* observer) {
	auto it = find(allObservers.begin(), allObservers.end(), observer);
	if (it != allObservers.end())
		allObservers.erase(it);
}

void Subject::notify() {
	qDebug() << "entered subject.notify";
	for (auto observer : allObservers)
		observer->update();
}
