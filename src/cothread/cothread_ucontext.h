#ifndef COTHREADUCONTEXT_H
#define COTHREADUCONTEXT_H

#include <stddef.h>
#include <sys/types.h>
#include <ucontext.h>
#include "cothread.h"

// ucontext based coroutine
class CothreadUcontext : public CoThread
{
private:
    ucontext_t m_ctx;
    static ucontext_t main_ctx;

    bool m_started;
    bool m_yielded;
public:
    CothreadUcontext(CoThreadFactory* factory);
    void reinit(CoThreadRoutine routine, void *user_data);
    void resume();
    void yield();

    CoThreadStatus status();
};

#endif // COTHREADUCONTEXT_H
