#ifndef COTASK_H
#define COTASK_H

#include "coevent/event.h"
#include "cothread/cothread.h"

class CoScheduler;
class CoSchedTask;


class CoTask
{
private:
    CoSchedTask *m_schedTask;
public:
    CoTask();
    virtual void exec() {}
    virtual void cancel() {}
    void done();
};

#endif // COTASK_H
