#ifndef COTASK_H
#define COTASK_H

#include "coevent/event.h"
#include "cothread/cotread.h"

class CoScheduler;
class CoSchedTask;


class CoTask
{
public:
    CoTask();
    virtual void exec() {}
    virtual void cancel() {}
    virtual void done() {}
};

#endif // COTASK_H
