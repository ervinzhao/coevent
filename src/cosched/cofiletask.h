#ifndef COFILETASK_H
#define COFILETASK_H

#include "cotask.h"
#include "cothread/cothread.h"

class CoFileTask : public CoTask, EventHandler
{
public:
    CoFileTask(CoTask *parentTask);
    void onRead(int fd);
    void onWrite(int fd);
    void onReadWrite(int fd);
    void onTimeout(int eventID) {}
    void onTimeEventRemoved() {}
};

#endif // COFILETASK_H
