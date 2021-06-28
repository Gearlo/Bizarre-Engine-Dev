
#include <BTTheadingContext.h>

BMutex::BMutex(){
    cond = PTHREAD_COND_INITIALIZER;
    mutex = PTHREAD_MUTEX_INITIALIZER;
}

BTThreadingContext::BTThreadingContext():
BThreadingContext()
{}

BThread * BTThreadingContext::createThread(void*(*__start_routine)(void*), void* __arg, BThreadId id){
    pthread_t newThread;
    pthread_create (&newThread , NULL , __start_routine , __arg);

    BThread * thread = new BThread(newThread);
    if( id != THREAD_NONE ){
        threads[id] = thread;
    }
    return thread;
}

void BTThreadingContext::waitSignal(BMutexId id){
    if ( !( id < MUTEXES_NUMBER ) || !( mutexes[id] )  )
        return;

    pthread_cond_t * cond = &( mutexes[id]->cond ); 
    pthread_mutex_t * mutex = &( mutexes[id]->mutex ); 

    pthread_mutex_lock(mutex);
    pthread_cond_wait(cond, mutex);
    pthread_mutex_unlock(mutex);   
}

void BTThreadingContext::throwSignal(BMutexId id){
    if ( !( id < MUTEXES_NUMBER ) || !( mutexes[id] )  )
        return;

    pthread_cond_t * cond = &( mutexes[id]->cond ); 
    pthread_mutex_t * mutex = &( mutexes[id]->mutex ); 

    pthread_mutex_lock(mutex);
    pthread_cond_signal(cond);
    pthread_mutex_unlock(mutex);
}