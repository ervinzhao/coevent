#ifndef COTHREADUCONTEXT_H
#define COTHREADUCONTEXT_H

#include <ucontext.h>
#include "cotread.h"

// ucontext based coroutine
class CothreadUcontext : public CoThread
{
private:
public:
    CothreadUcontext();
    void resume();
    void yield();
};

#endif // COTHREADUCONTEXT_H
