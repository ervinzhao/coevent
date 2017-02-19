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

void CoSchedTask::onTimeout(int eventID)
{
    m_sched->wakeThread(this);
}

void CoSchedTask::onRead()
{
    done();
}

void CoSchedTask::onWrite()
{
    done();
}

void CoSchedTask::onReadWrite()
{
    done();
}

void CoSchedTask::onTimeout()
{
    done();
}

void CoSchedTask::onTimeEventRemoved()
{
    done();
}

void CoSchedTask::done()
{
    if(m_sched && m_thread)
        m_sched->wakeThread(m_thread);
    else
        ; // assert(0);
}

bool CoSchedTask::shouldWake(CoTask *)
{
    return true;
}
