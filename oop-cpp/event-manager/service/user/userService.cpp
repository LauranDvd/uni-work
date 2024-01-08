#include "userService.h"
#include <algorithm>
#include "event.h"
#include <iterator>
#include "eventRepository.h"
#include "memoryEventRepository.h"
#include "idNotFoundInShortlistException.h"

// if [month] is -1, returns all events
std::vector<Event> UserService::getAllEventsInMonth(int month) {
    std::vector<Event> allEvents = repository->getAll();
    sort(allEvents.begin(), allEvents.end(), [](const Event firstInVector, const Event secondInVector) {
        return secondInVector.getDate() > firstInVector.getDate() ||
            (secondInVector.getDate() == firstInVector.getDate() && secondInVector.getHour() > firstInVector.getHour());
        });

    if (month == -1)
        return allEvents;

    std::vector<Event> allInMonth;
    copy_if(allEvents.begin(), allEvents.end(), back_inserter(allInMonth), [month](const Event gathering) {return gathering.getMonth() == month;});

    return allInMonth;
}

std::vector<Event> UserService::getEventsInShortlist() {
    std::vector<Event> interestedInEvents;

    for (int idWhichInterestsUser : shortlist->getAllIds())
        interestedInEvents.push_back(repository->findById(idWhichInterestsUser));

    return interestedInEvents;
}

void UserService::addShortlist(int eventId) {
    shortlist->addEventId(eventId);
    repository->incrementAttendance(eventId);
}

void UserService::deleteShortlist(int eventId) {
    shortlist->removeEventId(eventId);
    repository->decrementAttendance(eventId);
}

std::string UserService::getShortlistPath() const {
    return shortlist->getFilename();
}

void UserService::seeShortlistExtern() const {
    shortlist->openExtern();
}
