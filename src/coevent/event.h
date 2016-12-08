#ifndef EVENT_H
#define EVENT_H

class EventHandler {
public:
    virtual void onRead() {}
    virtual void onWrite() {}
    virtual void onReadWrite() {}
    virtual void onTimeout() {}
    virtual void onTimeEventRemoved() {}
};

#endif // EVENT_H
