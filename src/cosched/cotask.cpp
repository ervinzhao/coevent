#include "cotask.h"
#include "coscheduler.h"

CoTask::CoTask()
{
    m_schedTask = t_scheduler->currentTask();
}

void CoTask::done()
{
    t_scheduler->finishTask(this, m_schedTask);
}
