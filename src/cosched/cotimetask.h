#ifndef COTIMETASK_H
#define COTIMETASK_H

#include "cotask.h"
#include "cothread/cothread.h"


class CoTimeTask : public CoTask, EventHandler
{
public:
    CoFileTask(CoTask *parentTask);
    void onRead(int fd);
    void onWrite(int fd);
    void onReadWrite(int fd);
    void onTimeout(int eventID) {}
    void onTimeEventRemoved() {}
};

#endif // COTIMETASK_H
