#ifndef __WD_H__
#define __WD_H__

typedef enum status
{
    SUCCESS = 0,
    SCHED_CREAT_FAIL,
    
    STATUSES;
    
}status_t;

status_t WDStart(char** args);

void WDStop(void);

#endif /* __WD_H__ */