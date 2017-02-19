#ifndef COTHREADUCONTEXT_H
#define COTHREADUCONTEXT_H

#include <ucontext.h>
#include "cotread.h"

// ucontext based coroutine
class CothreadUcontext : public CoThread
{
private:
    ucontext_t m_ctx;
    static ucontext_t main_ctx;
public:
    CothreadUcontext();
    void run(CoThreadRoutine routine);
    void resume();
    void yield();

};

#endif // COTHREADUCONTEXT_H
