#ifndef COSCHEDULER_H
#define COSCHEDULER_H

#include <map>

#include "coevent/event.h"
#include "coevent/event_loop.h"
#include "cothread/cotread.h"
#include "cotask.h"
#include "coschedtask.h"


class CoScheduler
{
private:
    static CoScheduler *s_scheduler = NULL;
private:
    EventLoop m_loop;
    CoSchedTask *m_currentTask;

    std::map<CoSchedTask *, CoSchedTask *> m_workingSet;
    std::map<CoSchedTask *, CoSchedTask *> m_sleepingSet;
public:
    CoScheduler();
    ~CoScheduler();

    void wakeThread(CoSchedTask *);
    void wakeThread(CoThread *);
    void run();

    void startRoutine();
    void stopRoutine();

    // Async Task Interface
    CoSchedTask *currentTask() {
        return m_currentTask;
    }

    void waitForTask(CoTask *, int timeout = 0);
    void finishTask(CoTask *, CoSchedTask *);

    // Sync Task Interface
    void waitForReadable(int fd, int timeout = 0);
    void waitForWritable(int fd, int timeout = 0);
    void sleep(int ms);
    void yield();

    static CoScheduler *scheduler() {
        if (s_scheduler == NULL)
            s_scheduler = new CoScheduler;
        return s_scheduler;
    }
};

#endif // COSCHEDULER_H
