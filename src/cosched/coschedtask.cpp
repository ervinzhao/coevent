#include "coschedtask.h"
#include "coscheduler.h"

CoSchedTask::CoSchedTask()
{
    m_sched = NULL;
    m_thread = NULL;

    m_waitingType = WaitingType::WaitingAll;
    m_waitingCount = 0;
    m_waitedCount = 0;
}

void CoSchedTask::reinit(CoScheduler *sched, CoThread *thread)
{
    m_sched = sched;
    m_thread = thread;
}

void CoSchedTask::onEvent()
{
    if(m_sched && m_thread)
        m_sched->wakeThread(this);
    else
        ; // assert(0);
}

void CoSchedTask::onRead(int fd)
{
    onEvent();
}

void CoSchedTask::onWrite(int fd)
{
    onEvent();
}

void CoSchedTask::onReadWrite(int fd)
{
    onEvent();
}

void CoSchedTask::onTimeout(int eventID)
{
    onEvent();
}

void CoSchedTask::onTimeEventRemoved()
{
    onEvent();
}

bool CoSchedTask::shouldWake(CoTask *)
{
    return true;
}
