#ifndef COTASK_H
#define COTASK_H

#include "coevent/event.h"
#include "cothread/cothread.h"

class CoScheduler;
class CoSchedTask;

class CoTask
{
    enum class TaskStatus {
        Init,
        Running,
        Finished,
    };
private:
    CoTask *m_parentTask;
    TaskStatus m_status;
public:
    CoTask();
    virtual void exec() {}
    virtual void cancel() {}
    void run(CoTask *parentTask) {
        m_parentTask = parentTask;
        if (m_status == TaskStatus::Init) {
            m_status = TaskStatus::Running;
            exec();
        }
    }

    void done();

    // default behavior, active parent task.
    virtual void active(CoTask *task) {
        done();
    }

    bool finished() {
        return m_status == TaskStatus::Finished;
    }
    bool running() {
        return m_status == TaskStatus::Running;
    }
};

#endif // COTASK_H
