
#include "context/shlock.h"
#include <fcntl.h>
#include <string>

shstd::lock::CCond::CCond()
{
    pthread_cond_init(&m_tCond, NULL);
}

shstd::lock::CCond::~CCond()
{
    pthread_cond_destroy(&m_tCond);
}

bool shstd::lock::CCond::Wait(shstd::lock::CMutex &mutex, int nMillisecond)
{
    timespec to;
    to.tv_sec = nMillisecond / 1000;
    to.tv_nsec = (nMillisecond % 1000) * 1000000;

    int  nRet = pthread_cond_timedwait(&m_tCond, &mutex.m_tMutex, &to);
    return nRet == 0;
}

bool shstd::lock::CCond::Notify()
{
    bool bRet = pthread_cond_signal(&m_tCond);
    return bRet;
}


shstd::lock::CMutex::CMutex()
{
    pthread_mutex_init(&m_tMutex, NULL);
}

shstd::lock::CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_tMutex);
}


bool shstd::lock::CMutex::Lock()
{
    return (0 == pthread_mutex_lock(&m_tMutex));
}


bool shstd::lock::CMutex::TryLock()
{
    return (0 == pthread_mutex_trylock(&m_tMutex));
}


bool shstd::lock::CMutex::Unlock()
{
    return (0 == pthread_mutex_unlock(&m_tMutex));
}
