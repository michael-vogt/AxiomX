#include "geoobject.h"

void GeoObject::update() {}

void GeoObject::notify() {
    // 1. Update model
    for (auto d : dependents) {
        d->update();
        d->notify();
    }

    // 2. Notify view
    for (auto obs : observers) {
        obs->sync();
    }
}

void GeoObject::addDependent(GeoObject* obj) {
    dependents.push_back(obj);
}

void GeoObject::removeDependent(GeoObject* obj) {
    dependents.erase(std::remove(dependents.begin(), dependents.end(), obj), dependents.end());
}

void GeoObject::addObserver(Observer* obs) {
    observers.push_back(obs);
}

void GeoObject::removeObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

GeoObject::~GeoObject() {}