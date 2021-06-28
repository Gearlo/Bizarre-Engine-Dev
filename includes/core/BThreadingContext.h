#ifndef _B_THREADING_CONTEXT_H
#define _B_THREADING_CONTEXT_H

class BThread;
enum BThreadId{
    THREAD_MAIN = 0,
    THREAD_ASSETS_LOAD,

    THREAD_NONE,
    THREADS_NUMBER = 2
};

enum BSemaphoreId{
    ASSETS_LIBRARY = 0,
    ASSETS_QUEUE = 1,

    SEMAPHORES_NUMBER = 2
};

class BMutex;
enum BMutexId{
    MUTEX_TEST,
    MUTEX_NONE,
    MUTEXES_NUMBER = 2
};



class BThreadingContext{
protected:
    BThreadingContext(void){}

public:
    virtual BThread * createThread(void *(*__start_routine) (void *), void *__restrict __arg = NULL, BThreadId id = THREAD_NONE) = 0;
    virtual void waitThread(   BThreadId id   ) = 0;
    virtual void waitThread( BThread * thread ) = 0;

    virtual void initSemaphore( BSemaphoreId semaphore )=0;
    virtual void     waitToUse( BSemaphoreId semaphore )=0;
    virtual void        endUse( BSemaphoreId semaphore )=0;

    virtual BMutex * initMutex( BMutexId id )=0;

    virtual void  waitSignal( BMutexId id )=0;
    virtual void throwSignal( BMutexId id )=0;

};

#endif
