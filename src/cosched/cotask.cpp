#include "cotask.h"
#include "coscheduler.h"

CoTask::CoTask()
{
    m_status = TaskStatus::Init;
}

void CoTask::done()
{
    m_status = TaskStatus::Finished;
    if(m_parentTask) {
        m_parentTask->active(this);
    }
}
