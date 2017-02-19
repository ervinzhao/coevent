#include "event_loop.h"

static void fileProc(struct aeEventLoop *eventLoop, int fd, void *clientData,
                     int mask)
{
    EventHandler *handler = (EventHandler *) clientData;
    if((mask & AE_READABLE) && mask & AE_WRITABLE) {
        handler->onReadWrite(fd);
    } else if(mask & AE_READABLE) {
        handler->onRead(fd);
    } else if(mask & AE_WRITABLE) {
        handler->onWrite(fd);
    }
}

static int timeoutProc(struct aeEventLoop *eventLoop, long long id, void *clientData)
{
    EventHandler *handler = (EventHandler *) clientData;
    handler->onTimeout(id);
}

static void timeEventRemovedProc(struct aeEventLoop *eventLoop, void *clientData)
{
    EventHandler *handler = (EventHandler *) clientData;
    handler->onTimeEventRemoved();
}

EventLoop::EventLoop()
{
    m_aeLoop = aeCreateEventLoop(102400);
}

void EventLoop::watchFileEvent(int fd, bool read, bool write, EventHandler *handler)
{
    int mask = 0;
    if(read) mask &= AE_READABLE;
    if(write) mask &= AE_WRITABLE;
    aeCreateFileEvent(m_aeLoop, fd, mask, &fileProc, (void *)handler);
}

long long EventLoop::watchTimeEvent(long long milliseconds, EventHandler *handler)
{
    aeCreateTimeEvent(m_aeLoop, milliseconds, &timeoutProc, (void *)handler,
                      &timeEventRemovedProc);
}

void EventLoop::deleteFileEvent(int fd, bool read, bool write)
{
    int mask = 0;
    if(read) mask &= AE_READABLE;
    if(write) mask &= AE_WRITABLE;
    if(mask == 0) return;
    aeDeleteFileEvent(m_aeLoop, fd, mask);
}

void EventLoop::deleteTimeEvent(long long eventID)
{
    aeDeleteTimeEvent(m_aeLoop, eventID);
}

void EventLoop::run()
{
    aeMain(m_aeLoop);
}
