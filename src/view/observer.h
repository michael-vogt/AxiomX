#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void sync() = 0;
    virtual ~Observer();
};

#endif // OBSERVER_H
