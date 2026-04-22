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
    virtual void update();

    void notify();

    void addDependent(GeoObject* obj);

    void removeDependent(GeoObject* obj);

    void addObserver(Observer* obs);

    void removeObserver(Observer* obs);

    virtual ~GeoObject();
};


#endif // GEOOBJECT_H
