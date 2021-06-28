#ifndef _B_TTHREADING_CONTEXT_H
#define _B_TTHREADING_CONTEXT_H

#include <BCore.h>

#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

/* 
#ifdef WIN32
    //#include <win32.h>
#else
    #include <sys/ipc.h>
    #include <semaphore.h>
#endif
*/


#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
    // La union ya está definida en sys/sem.h
#else
    // Tenemos que definir la union
    union semun 
    { 
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
        struct seminfo *__buf;
    };
#endif


class BThread{
private:    
    pthread_t thread;

friend class BTThreadingContext;
public:
    inline BThread(pthread_t thread){ this->thread = thread; }
};


class BMutex{
private:
    pthread_cond_t cond; 
    pthread_mutex_t mutex; 

    friend class BTThreadingContext;
public:
    inline BMutex(void);
    
};


class BTThreadingContext : public BThreadingContext{
private:
    sem_t semaphores[SEMAPHORES_NUMBER];
    BThread * threads[THREADS_NUMBER];
    BMutex * mutexes[MUTEXES_NUMBER];

    bool ended;  

protected:
    BTThreadingContext();

public:
    
    // threads
    BThread * createThread(void *(*__start_routine) (void *), void *__restrict __arg = NULL, BThreadId id = THREAD_NONE);
    inline void waitThread(  BThreadId id ){ if(id < THREAD_NONE && threads[id])pthread_join (threads[id]->thread, NULL ); }
    inline void waitThread( BThread * thread ){ pthread_join ( thread->thread, NULL ); }

    inline bool isThisThread( BThreadId id ){ return ( threads[id] )? pthread_equal(pthread_self(), threads[id]->thread): false; }

    // semaphores
    inline void initSemaphore( BSemaphoreId semaphore ){ if(semaphore < SEMAPHORES_NUMBER ) sem_init( &(semaphores[semaphore]), 0, 1); }
    inline void waitToUse(BSemaphoreId semaphore){ if(semaphore < SEMAPHORES_NUMBER ) sem_wait( &(semaphores[semaphore]) ); }
    inline void endUse(BSemaphoreId semaphore){ if(semaphore < SEMAPHORES_NUMBER ) sem_post( &(semaphores[semaphore]) ); }

    //mutex
    inline BMutex * initMutex( BMutexId id ){ if( id < MUTEXES_NUMBER ) mutexes[id] = new BMutex(); }
    void waitSignal( BMutexId id );
    void throwSignal( BMutexId id );


    static inline BTThreadingContext * getInstance(void){ static BTThreadingContext instance; return &instance; }
};


#endif


