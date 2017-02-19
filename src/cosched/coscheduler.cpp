#include "coscheduler.h"

CoScheduler::CoScheduler()
{
    m_currentUnit = NULL;
}

CoScheduler::~CoScheduler()
{

}

void CoScheduler::wakeThread(CoSchedTask *unit)
{
    CoSchedTask *u = m_sleepingSet[unit];
    if(u != m_sleepingSet.end()) {
        m_sleepingSet.erase(unit);

        m_workingSet[unit] = u;
    }
}

void CoScheduler::wakeThread(CoThread *thread)
{
    wakeThread((CoSchedTask *) thread);
}

void CoScheduler::run()
{
    while(true) {
        auto first = m_workingSet.begin();
        if (first != m_workingSet.end()) {
            CoSchedTask *unit = first->second;
            m_workingSet.erase(first);

            m_currentTask = unit;
            m_currentTask->thread->resume();
            m_currentTask = NULL;

            int status = m_currentTask->thread->status();
            if(status == 0) {
                // Release this schedule unit.
            } else {
                m_sleepingSet[unit] = unit;
            }
        }
        m_loop.run();
    }
}

void CoScheduler::finishTask(CoTask *task, CoSchedTask *schedTask)
{
    bool shouldWake = schedTask->shouldWake(task);
    if (shouldWake) {
        this->wakeThread(schedTask);
    }
}

void CoScheduler::sleep(int ms)
{
    if (m_currentTask == NULL)
        return
    m_loop.watchTimeEvent(ms, m_currentTask);

}

void CoScheduler::yield()
{
    if(m_currentTask == NULL)
        return;
    CoThread * thread = m_currentTask->m_thread;
    m_currentTask = NULL;
    thread->yield();
}
