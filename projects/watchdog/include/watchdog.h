#ifndef __WD_H__
#define __WD_H__

#include <time.h>

typedef enum status
{
    SUCCESS = 0,
    REVIVE_USR_PROC_FAILURE,
    SCHED_CREATE_FAILURE,
    THREAD_CREATE_FAILURE,
    DAEMON_CREATE_FAILURE,
    STOP_TIMEOUT
}wd_status_t;

wd_status_t WDStart(char* args[]);

wd_status_t WDStop(time_t timeout);

#endif /*__WD_H__*/