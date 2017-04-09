#include "cothread.h"
#include "cothread_factory.h"

CoThread::CoThread(CoThreadFactory *factory)
{
    m_factory = factory;
}

void CoThread::recycle()
{
    if(m_factory) {
        m_factory->recycle(this);
    } else {
        delete this;
    }
}

