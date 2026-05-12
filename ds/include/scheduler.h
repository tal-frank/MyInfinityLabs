#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__


#include "task.h" /* task API */
#include "priority_queue.h" /* priority queue API */
#include "uid.h" /* uid API */


typedef struct Scheduler sched_t;

/****************************************************************************
* 		
* Description: Creats a new scheduler to schedual tasks.
*		        
*   Arguments: None
*		
*      Return: A pointer to the new schedualer. NULL if fails.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
sched_t* SchedCreate(void);

/*****************************************************************************
* 		
* Description: destroys a scheduler.
*		        
*   Arguments: sched - A valid ptr to scheduler.
*		
*      Return: None
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

void SchedDestroy(sched_t* sched);

/**************************************************************** *
* 		
* Description: Adds a new task to the scheduler.
*		        
*   Arguments: sched       - A valid ptr to scheduler.
*              interval    - Itervals time between runs of a task.
*              time_to_run - When to run the task.
*	       op_func     - The task to-do.
*	       clean_func  - Cleans all the allocated parameters in task if there are any.
*	       params      - Arguments for the op_func.
*
*      Return: uid_t of the added task. UIDBadUID if fails.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
ilrd_uid_t SchedTaskAdd(sched_t* sched,
                   size_t interval,
                   time_t time_to_run,
                   int (*op_func)(void* param),
                   int (*clean_func)(void* param),
                   void* param);

/****************************************************************************
* 		
* Description: Removes a task from a schaduler. 
*		        
*   Arguments: sched - A valid ptr to scheduler, 
*              uid   - Task identifier of the task to be removed.
*            
*      Return: 0 for success 1 for failure. 
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
/* need to create a static function in sched in order to pass it to PQErase,
    static int TaskIsMatch( task_t* task, ilrd_uid_t* uid) 
*/
int SchedTaskRemove(sched_t* sched, ilrd_uid_t uid);

/****************************************************************************
* 		
* Description: Start Running the tasks one by one until stop task apears 
*              or end of tasks. 
*		        
*   Arguments: sched - A valid pointer to a scheduler.
*            
*      Return: 0 for normal status non-zero for other status.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
int SchedRun(sched_t* sched);

/****************************************************************************
* 		
* Description: Stops the running of SchedRun function.
*		        
*   Arguments: sched - A valid pointer to a scheduler to stop.
*            
*      Return: None.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void SchedStop(sched_t* sched);

/****************************************************************************
* 		
* Description: Checks if a schedualer is empty.
*		        
*   Arguments: sched - A valid pointer to a scheduler to cxheck for emptyness.
*            
*      Return: 1 if empty 0 if not.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int SchedIsEmpty(const sched_t* sched);

/****************************************************************************
* 		
* Description: Counts the number of tasks currently in the schedualer.
*		        
*   Arguments: sched - A valid pointer to a scheduler to count tasks in.
*            
*      Return: number of thask currently in the schedualer.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

size_t SchedCount(const sched_t* sched);

/****************************************************************************
* 		
* Description: Empties the schedualer from tasks.
*		        
*   Arguments: sched - A valid pointer to a scheduler to empty.
*            
*      Return: None.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

void SchedClear(sched_t* sched);



#endif /** End of __SCHEDULER_H__ */
