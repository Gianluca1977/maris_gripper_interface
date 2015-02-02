#ifndef RT_THREAD_H
#define RT_THREAD_H

#include <pthread.h>

#define MAX_NAMES_SIZE	32

class rt_thread
{    
    char if_label[MAX_NAMES_SIZE];

protected:
    pthread_t if_thread;
    void* returnValue;

public:
    rt_thread(){//if_thread.Create(thread_func, this);
                returnValue = NULL;}
    virtual ~rt_thread(void);
    virtual void rt_thread_handler(void)=0;
    static void *thread_func(void* p);
    //void set_label(char *str){sprintf(if_label,str);}
    //char* get_label(void){return if_label;}
};

#endif // RT_THREAD_H
