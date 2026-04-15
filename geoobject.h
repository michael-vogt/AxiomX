#ifndef GEOOBJECT_H
#define GEOOBJECT_H

#include <vector>
#include "observer.h"

namespace Core {
class GeoObject;
}

class GeoObject {
protected:
    std::vector<GeoObject*> dependents;
    std::vector<Observer*> observers;

public:
    virtual void update() = 0;

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

    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    virtual ~GeoObject() {}
};


#endif // GEOOBJECT_H
