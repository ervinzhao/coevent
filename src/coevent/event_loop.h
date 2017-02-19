#ifndef EVENTLOOP_H
#define EVENTLOOP_H

extern "C" {
#include "ae.h"
}
#include "event.h"

class EventLoop
{
private:
    aeEventLoop *m_aeLoop;
public:
    EventLoop();
    ~EventLoop();

    void watchFileEvent(int fd, bool read, bool write, EventHandler *handler);
    long long watchTimeEvent(long long milliseconds, EventHandler *handler);
    void deleteFileEvent(int fd, bool read, bool write);
    void deleteTimeEvent(long long eventID);

    void run();
};

#endif // EVENTLOOP_H
