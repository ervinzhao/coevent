#ifndef COTREAD_H
#define COTREAD_H

typedef void (*CoThreadRoutine)(void *);

class CoTread
{
private:
    // sleeping/running/waiting
    int m_status;
public:
    CoTread();
    virtual ~CoThread();
    virtual void run(CoThreadRoutine routine);
    virtual void resume() = 0;
    virtual void yield() = 0;
    int status();
};

#endif // COTREAD_H
