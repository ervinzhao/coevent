#ifndef COSCHEDTASK_H
#define COSCHEDTASK_H

#include <vector>
#include "cotask.h"
#include "cothread/cothread.h"

class CoScheduler;
class CoThread;

class CoSchedTask : public CoTask, public EventHandler
{
private:
    CoThread *m_thread;
    CoScheduler *m_sched;

    enum class WaitingType {
        WaitingAll,
        WaitingAny,
        WaitingCount,
    };
    std::vector<CoTask *> m_waitingTasks;
    WaitingType m_waitingType;
    int m_waitingCount;
    int m_waitedCount;
public:
    CoSchedTask();
    ~CoSchedTask();
    void reinit(CoScheduler *, CoThread *);
    void onEvent();
    void onRead(int fd);
    void onWrite(int fd);
    void onReadWrite(int fd);
    void onTimeout(int eventID);
    void onTimeEventRemoved();

    void exec() {}
    void cancel() {}

    bool shouldWake(CoTask *);
    friend class CoScheduler;
};


#endif // COSCHEDTASK_H
