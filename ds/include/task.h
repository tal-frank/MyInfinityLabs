#ifndef __TASK_H__
#define __TASK_H__

#include <sys/types.h> /* time_t, size_t*/

#include "uid.h" /* uid API */

typedef struct Task task_t;

/****************************************************************************
* 		
* Description: Creates a new task.
*		        
*   Arguments: interval    - A relative time to add to the time to run 
*			     after execution for update when to run again.
*	       time to run - An absolute time to run the task.
*	       op_func     - Task to be executed.
*	       clean_func  - 
*	       param       - 
*            
*      Return: A pointer to the task.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

task_t* TaskCreate(size_t interval,
                   time_t time_to_run,
                   int (*op_func)(void* params),
                   int (*clean_func)(void* params),
                   void* params);

/****************************************************************************
* 		
* Description: Destroys a task.
*		        
*   Arguments: task - A valid pointer to a task to destroy.
*            
*      Return: None.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void TaskDestroy(task_t* task);

/****************************************************************************
* 		
* Description: Fetches the UID of a task.
*		        
*   Arguments: task - A valid pointer to a task to get the UID of.
*            
*      Return: UID of a task.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

ilrd_uid_t TaskGetUid(const task_t* task);

/****************************************************************************
* 		
* Description: Runs a task's operation function.
*		        
*   Arguments: task - A valid pointer to a task to run it's 
*            
*      Return: 0 for success, none 0 for none success.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int TaskRun(task_t* task);

/****************************************************************************
* 		
* Description: Updates the time to run of a task after it has been executed
*	       (if interval is none 0).
*		        
*   Arguments: task - A valid pointer to a task to update it's time to run.
*            
*      Return: None.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void TaskUpdateTimeToRun(task_t* task);

/****************************************************************************
* 		
* Description: fetches the time to run of a task.
*		        
*   Arguments: task - A valid pointer to a task to fetch it's time to run.
*            
*      Return: None.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

time_t TaskGetTimeToRun(const task_t* task);

/****************************************************************************
* 		
* Description: Checks if a task is to be repeated.
*		        
*   Arguments: task - A valid pointer to a task to check if repeatable.
*            
*      Return: 1 if repeatable, 0 if not.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int TaskIsRepeatable(const task_t* task);

/****************************************************************************
* 		
* Description: Checks if two tasks are same.
*		        
*   Arguments: task1 - a valid pointer to a task to compare.
*	       task2 - a valid pointer to a task to compare.
*            
*      Return: 1 if equal, none 0 if not.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int TaskIsEqual(const task_t* task1, const task_t* task2);


#endif /** __TASK_H__ */
