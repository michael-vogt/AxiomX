#ifndef GEOOBJECT_H
#define GEOOBJECT_H

#include <vector>
#include "../view/observer.h"

class GeoObject {
protected:
    std::vector<GeoObject*> dependents;
    std::vector<Observer*> observers;

public:
    virtual void update();

    void notify();

    void addDependent(GeoObject* obj);

    void addObserver(Observer* obs);

    virtual ~GeoObject();
};


#endif // GEOOBJECT_H
