#ifndef COSCHEDULER_H
#define COSCHEDULER_H

#include <map>

#include "coevent/event.h"
#include "coevent/event_loop.h"
#include "cothread/cothread.h"
#include "cothread/cothread_factory.h"
#include "cotask.h"
#include "coschedtask.h"

class CoScheduler;
extern thread_local CoScheduler *t_scheduler;

class CoScheduler
{
private:
    EventLoop m_loop;
    CoSchedTask *m_currentTask;

    std::map<CoSchedTask *, CoSchedTask *> m_workingSet;
    std::map<CoSchedTask *, CoSchedTask *> m_sleepingSet;

    CoScheduler() {
        m_currentTask = NULL;
    }
public:
    ~CoScheduler();

    void createThread(CoThreadFactory *factory, CoThreadRoutine, void *user_data);
    void addThread(CoSchedTask *);
    void run();    

    // Async Task Interface
    CoSchedTask *currentTask() {
        return m_currentTask;
    }
    EventLoop *currentEventLoop() {
        return m_loop;
    }

    void runAsyncTask(CoTask *task);
    void waitAsyncTask(CoTask *task, int timeout = 0);
    void waitForReadable(int fd, int timeout = 0);
    void waitForWritable(int fd, int timeout = 0);
    void sleep(int ms);
    void yield();
    void wakeThread(CoSchedTask *);

    static CoScheduler *scheduler() {
        return t_scheduler;
    }
    static CoScheduler *createScheduler() {
        t_scheduler = new CoScheduler;
        return t_scheduler;
    }
};

#endif // COSCHEDULER_H
