#ifndef COSCHEDTASK_H
#define COSCHEDTASK_H

#include <vector>
#include "cotask.h"
#include "cofiletask.h"
#include "cotimetask.h"
#include "cothread/cothread.h"

class CoScheduler;
class CoThread;

class CoSchedTask : public CoTask
{
private:
    CoThread *m_thread;
    CoScheduler *m_sched;
    CoFileTask m_fileTask;
    CoTimeTask m_timeTask;

    int m_timeoutCount;
public:
    CoSchedTask();
    ~CoSchedTask();
    void reinit(CoScheduler *, CoThread *);

    void exec() {}
    void cancel() {}
    void active(CoTask *subTask);

    friend class CoScheduler;
};


#endif // COSCHEDTASK_H
