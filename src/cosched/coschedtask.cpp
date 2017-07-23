#include "coschedtask.h"
#include "coscheduler.h"

CoSchedTask::CoSchedTask()
{
    m_sched = NULL;
    m_thread = NULL;
}

void CoSchedTask::reinit(CoScheduler *sched, CoThread *thread)
{
    m_sched = sched;
    m_thread = thread;
}

void CoSchedTask::active(CoTask *subTask)
{
    m_sched->wakeThread(this);
}

