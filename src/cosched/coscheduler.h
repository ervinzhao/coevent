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

    // Run task and set m_currentTask as it's parent task
    void runAsyncTask(CoTask *task);

    // Run task,
    // if it's already running, run it as sub task of m_currentTask.
    // waiting until it's finished.
    void waitAsyncTask(CoTask *task, int timeout = 0);
    bool waitForReadable(int fd, int timeout = 0);
    bool waitForWritable(int fd, int timeout = 0);
    void sleep(int ms);
    void yield();

    void switchOnThread(CoSchedTask *task);
    void switchOffThread(CoSchedTask *task);

    static CoScheduler *scheduler() {
        return t_scheduler;
    }
    static CoScheduler *createScheduler() {
        t_scheduler = new CoScheduler;
        return t_scheduler;
    }
};

#endif // COSCHEDULER_H
