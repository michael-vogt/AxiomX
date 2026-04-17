#ifndef GEOOBJECT_H
#define GEOOBJECT_H

#include <algorithm>
#include <vector>
#include "../view/observer.h"

class GeoObject {
protected:
    std::vector<GeoObject*> dependents;
    std::vector<Observer*> observers;

public:
    virtual void update() {}

    void notify() {
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

    void addDependent(GeoObject* obj) {
        dependents.push_back(obj);
    }

    void removeDependent(GeoObject* obj) {
        dependents.erase(std::remove(dependents.begin(), dependents.end(), obj), dependents.end());
    }

    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    virtual ~GeoObject() {}
};


#endif // GEOOBJECT_H
