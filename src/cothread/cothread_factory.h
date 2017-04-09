#ifndef COTHREADFACTORY_H
#define COTHREADFACTORY_H

#include "cothread.h"

class CoThreadFactory
{
public:
    CoThreadFactory() {

    }
    ~CoThreadFactory() {

    }
    virtual void reserve(int count);
    virtual CoThread *create() = 0;
    virtual void recycle(CoThread *thread);
};

template<class CoThreadT>
class CoThreadFactoryT : public CoThreadFactory
{
public:
    void reserve(int count) {
        // Do nothing
    }
    CoThread *create() {
        CoThreadT *thread = new CoThreadT(this);
        return thread;
    }
    void recycle(CoThread *thread) {
        delete thread;
    }
};

#endif // COTHREADFACTORY_H
