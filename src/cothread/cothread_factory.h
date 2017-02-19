#ifndef COTHREADFACTORY_H
#define COTHREADFACTORY_H

#include "cothread.h"

template<class CothreadT>
class CothreadFactory
{
public:
    CothreadFactory();
    ~CothreadFactory();
    void reserve(int count);
    CothreadT *create();
    void recyle(CothreadT *thread);
};

#endif // COTHREADFACTORY_H
