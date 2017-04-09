#ifndef COTREAD_H
#define COTREAD_H

class CoThreadFactory;
typedef void (*CoThreadRoutine)(void *);

enum class CoThreadStatus
{
    Waiting,
    Running,
    Sleeping,
};

class CoThread
{
private:
    CoThreadFactory *m_factory;
public:
    CoThread(CoThreadFactory *factory);
    virtual ~CoThread();
    virtual void reinit(CoThreadRoutine routine, void *user_data);
    virtual void resume() = 0;
    virtual void yield() = 0;
    virtual CoThreadStatus status() = 0;
    void recycle();
};

#endif // COTREAD_H
