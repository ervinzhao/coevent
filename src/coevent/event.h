#ifndef EVENT_H
#define EVENT_H

class EventHandler {
public:
    virtual void onRead(int fd) {}
    virtual void onWrite(int fd) {}
    virtual void onReadWrite(int fd) {}
    virtual void onTimeout(int eventID) {}
    virtual void onTimeEventRemoved() {}
};

#endif // EVENT_H
