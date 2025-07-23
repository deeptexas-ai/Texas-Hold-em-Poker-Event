#ifndef __SH_STD_SAFE_LOCK__IN_
#define __SH_STD_SAFE_LOCK__IN_
#include <pthread.h>

namespace shstd
{
    namespace lock
    {

        class CMutex;
        class CCond
        {
        private:
            pthread_cond_t m_tCond;
        public:
            CCond();
            virtual ~CCond();
            bool Wait(CMutex &mutex, int nMillisecond);
            bool Notify();
        };

        class CMutex
        {
        protected:
            pthread_mutex_t m_tMutex;
            friend class CCond;
        public:
            CMutex();
            virtual ~CMutex();

            bool Lock();
            bool TryLock();
            bool Unlock();
        };

        class CSafeMutex
        {
            CMutex &m_mutex;
            CSafeMutex();
            bool m_bLock;
        public:
            CSafeMutex(CMutex &mutex, bool bTryLock = false) : m_mutex(mutex)
            {
                if (bTryLock)
                    m_bLock = m_mutex.TryLock();
                else
                    m_bLock = m_mutex.Lock();
            }
            bool IsLocked()
            {
                return m_bLock;
            }
            ~CSafeMutex()
            {
                if (m_bLock)
                {
                    m_mutex.Unlock();
                }
            }
        };
    }
}

#endif







