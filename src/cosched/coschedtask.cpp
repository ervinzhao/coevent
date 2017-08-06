#include "coschedtask.h"
#include "coscheduler.h"

CoSchedTask::CoSchedTask()
    : m_fileTask(this)
{
    m_sched = NULL;
    m_thread = NULL;
    m_timeoutCount = 0;
}

void CoSchedTask::reinit(CoScheduler *sched, CoThread *thread)
{
    m_sched = sched;
    m_thread = thread;
}

void CoSchedTask::active(CoTask *subTask)
{
    if(subTask == &m_timeTask)
        m_timeoutCount ++;
    m_sched->switchOnThread(this);
}

