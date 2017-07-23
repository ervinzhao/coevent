#include "coscheduler.h"


thread_local CoScheduler *t_scheduler = NULL;

CoScheduler::~CoScheduler()
{

}

void CoScheduler::wakeThread(CoSchedTask *task)
{
    auto iter = m_sleepingSet.find(task);
    if(iter != m_sleepingSet.end()) {
        m_sleepingSet.erase(iter);
        m_workingSet[task] = task;
    }
}

void CoScheduler::run()
{
    while(true) {
        auto first = m_workingSet.begin();
        if (first != m_workingSet.end()) {
            CoSchedTask *unit = first->second;
            m_workingSet.erase(first);

            m_currentTask = unit;
            m_currentTask->m_thread->resume();
            m_currentTask = NULL;

            CoThreadStatus status = unit->m_thread->status();
            if(status == CoThreadStatus::Waiting) {
                unit->m_thread->recycle();
                unit->m_thread = NULL;
                delete unit;
            } else {
                m_sleepingSet[unit] = unit;
            }
        }
        m_loop.run();
    }
}


void CoScheduler::createThread(CoThreadFactory *factory,
                               CoThreadRoutine routine, void *user_data)
{
    CoSchedTask *task = new CoSchedTask;
    CoThread *thread = factory->create();
    thread->reinit(routine, user_data);
    task->reinit(this, thread);

    m_workingSet[task] = task;
}

void CoScheduler::addThread(CoSchedTask *thread)
{
    m_workingSet[thread] = thread;
}

void CoScheduler::runAsyncTask(CoTask *task)
{
    task->run(m_currentTask);
}

void CoScheduler::waitAsyncTask(CoTask *task, int timeout)
{
    if(!task->finished()) {
        if(!task->running()) {
            task->run(m_currentTask);
        }

        m_currentTask->m_waitingType = CoSchedTask::WaitingType::Task;
        m_currentTask->m_waitingValue.task = task;
        m_loop.watchTimeEvent(timeout, m_currentTask);
    }
}

void CoScheduler::waitForReadable(int fd, int timeout)
{

}

void CoScheduler::waitForWritable(int fd, int timeout)
{

}

void CoScheduler::sleep(int ms)
{
    if (m_currentTask == NULL)
        return;
    m_loop.watchTimeEvent(ms, m_currentTask);
    yield();
}

void CoScheduler::yield()
{
    if(m_currentTask == NULL)
        return;
    CoThread * thread = m_currentTask->m_thread;
    m_currentTask = NULL;
    thread->yield();
}
