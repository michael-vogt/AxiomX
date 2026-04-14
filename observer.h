#ifndef OBSERVER_H
#define OBSERVER_H

namespace View {
class Observer;
}

class Observer {
public:
    virtual void sync() = 0;
    virtual ~Observer() {}
};

#endif // OBSERVER_H
