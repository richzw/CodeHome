#include <windows.h>

class FastReadWriteLock
{
public:        

    FastReadWriteLock()
    {
        m_lockState = 0; // init state
        m_hReadSem = CreateSemaphore(0,0,0x10000,0); // create ananymous semaphores with maximum value much larger
        m_hWriteSem = CreateSemaphore(0,0,0x10000,0); // than any possible value of waiting count fields
    }

    ~FastReadWriteLock()
    {
        CloseHandle(m_hReadSem); // release semaphores
        CloseHandle(m_hWriteSem);
    }

    void WaitForReadLock()
    {
        while (true)
        {
            LockState lockState = m_lockState; // get local copy of lock state
            if (lockState.writeLock || lockState.writeWaiting || lockState.readLock == -1) // write lock is held/pending or read lock overflow
            {
                if (lockState.readWaiting == -1) Sleep(0); // wait overflow; force a context switch in lieu of proper waiting
                else
                {
                    LockState newState = lockState; newState.readWaiting++; // create new state with incremented wait
                    if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) // wait aquired successfully
                    {
                        WaitForSingleObject(m_hReadSem,INFINITE); // block until an unlock event occurs
                        while (true) // attempt to decrement wait count until successful
                        {
                            lockState = m_lockState; // update local copy of lock state
                            newState = lockState; newState.readWaiting--; // create new state with decremented wait
                            if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) break; // wait released successfully
                        }
                    }
                }
            }
            else
            {                
                LockState newState = lockState; newState.readLock++; // create new state with incremented read lock count
                if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) break; // lock aquired successfully
            }
        } // loop continues if state was modified concurrently or wait expired
    }

    bool TryReadLock()
    {
        LockState lockState = m_lockState; // get local copy of lock state
        if (lockState.writeLock || lockState.writeWaiting || lockState.readLock == -1) return false; // write lock is held/pending or read lock overflow
        LockState newState = lockState; newState.readLock++; // create new state with incremented read lock count
        return lockState == InterlockedCompareExchange(&m_lockState,newState,lockState); // attempt to aquire lock
    }

    void ReleaseReadLock()
    {
        LockState lockState = m_lockState; // get local copy of lock state
        while (lockState.readLock) // attempt to decrement read lock until successful
        {
            LockState newState = lockState; newState.readLock--; // create new state with decremented read lock count
            if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) break; // lock released successfully
            lockState = m_lockState; // failure, reset local state copy
        } 
        if (lockState.writeWaiting)
        {
            ReleaseSemaphore(m_hWriteSem,1,NULL); // release a single waiting writer
        }
        else if (lockState.readWaiting)
        {
            ReleaseSemaphore(m_hReadSem,lockState.readWaiting,NULL); // release all waiting readers
        }
    }

    void WaitForWriteLock()
    {
        while (true)
        {
            LockState lockState = m_lockState; // get local copy of lock state
            if (lockState.writeLock || lockState.readLock) // read or write lock is currently held
            {
                if (lockState.writeWaiting == -1) Sleep(0); // wait overflow; force a context switch in lieu of proper waiting
                else
                {
                    LockState newState = lockState; newState.writeWaiting++; // create new state with incremented wait
                    if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) // wait aquired successfully
                    {
                        WaitForSingleObject(m_hWriteSem,INFINITE); // block until an unlock event occurs
                        while (true) // attempt to decrement wait count until successful
                        {
                            lockState = m_lockState; // update local copy of lock state
                            newState = lockState; newState.writeWaiting--; // create new state with decremented wait
                            if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) break; // wait released successfully
                        }
                    }
                }
            }
            else
            {                
                LockState newState = lockState; newState.writeLock = 1; // create new state with write lock
                if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) break; // lock aquired successfully
            }
        } // loop continues if state was modified concurrently or wait expired
    }

    bool TryWriteLock()
    {
        LockState lockState = m_lockState; // get local copy of lock state
        if (lockState.writeLock || lockState.readLock) return false; // read or write lock is currently held
        LockState newState = lockState; newState.writeLock = 1; // create new state with write lock
        return lockState == InterlockedCompareExchange(&m_lockState,newState,lockState); // attempt to aquire lock
    }

    void ReleaseWriteLock()
    {
        LockState lockState = m_lockState; // get local copy of lock state
        while (lockState.writeLock) // attempt to zero write lock until successful
        {
            LockState newState = lockState; newState.writeLock = 0; // create new state with no write lock
            if (lockState == InterlockedCompareExchange(&m_lockState,newState,lockState)) break; // lock released successfully
            lockState = m_lockState; // failure, reset local state copy
        } 
        if (lockState.writeWaiting)
        {
            ReleaseSemaphore(m_hWriteSem,1,NULL); // release a single waiting writer
        }
        else if (lockState.readWaiting)
        {
            ReleaseSemaphore(m_hReadSem,lockState.readWaiting,NULL); // release all waiting readers
        }
    }

protected:

    struct LockState
    {
        // state encoded in 32 bit word
        unsigned long   readWaiting     :11,
                        readLock        :11,                    
                        writeWaiting    :9,
                        writeLock       :1;
        // methods
        inline LockState(LONG value = 0) { *(LONG*)this = value; }
        inline operator LONG() const { return *reinterpret_cast<const unsigned long*>(this); }
        inline LockState& operator =(LONG value) { *(LONG*)this = value; return *this; }
        inline LockState& operator =(const LockState& rhs) { *(LONG*)this = (LONG)rhs; return *this; }
        inline bool operator ==(LONG value) const { return (LONG)*this == value; }
    };

    volatile LONG   m_lockState;
    HANDLE          m_hReadSem;
    HANDLE          m_hWriteSem;
};
