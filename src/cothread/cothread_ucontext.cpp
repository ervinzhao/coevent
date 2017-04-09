#include "cothread_ucontext.h"

typedef void (*makecontext_func_t)();

CothreadUcontext::CothreadUcontext(CoThreadFactory *factory)
    : CoThread(factory)
{
    ssize_t stacksize = 1024 * 8;
    ::getcontext(&m_ctx);
    m_ctx.uc_stack.ss_sp = new char[stacksize];
    m_ctx.uc_stack.ss_size = stacksize;

    m_started = false;
    m_yielded = false;
}

void CothreadUcontext::reinit(CoThreadRoutine routine, void *user_data)
{
    // Need checking current status.
    ::makecontext(&m_ctx, (makecontext_func_t) routine, 1, user_data);
    m_started = false;
}

void CothreadUcontext::resume()
{
    m_started = true;
    ::swapcontext(&main_ctx, &m_ctx);
    m_started = false;
}

void CothreadUcontext::yield()
{
    m_yielded = true;
    ::swapcontext(&m_ctx, &main_ctx);
    m_yielded = false;
}

CoThreadStatus CothreadUcontext::status()
{
    if(m_yielded)
        return CoThreadStatus::Sleeping;
    else
    {
        if(m_started)
            return CoThreadStatus::Running;
        else
            return CoThreadStatus::Waiting;
    }
}
