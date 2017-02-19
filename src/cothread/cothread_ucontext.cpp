#include "cothread_ucontext.h"

CothreadUcontext::CothreadUcontext()
{
    ssize_t stacksize = 1024 * 8;
    ::getcontext(&m_ctx);
    m_ctx.uc_stack.ss_sp = new char[stacksize];
    m_ctx.uc_stack.ss_size = stacksize;
}

void CothreadUcontext::run(CoThreadRoutine routine)
{
    // Need checking current status.
    ::makecontext(&m_ctx, (makecontext_func_t) routine, 0);
    ::swapcontext(&main_ctx, &m_ctx);
}

void CothreadUcontext::resume()
{
    ::swapcontext(&main_ctx, &m_ctx);
}

void CothreadUcontext::yield()
{
    ::swapcontext(&m_ctx, &main_ctx);
}
