#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <sys/types.h>

#define IPSIZE (14)

typedef struct Unique_id
{
	pid_t pid;
	time_t time;
	size_t counter;
	char ip[IPSIZE];
} ilrd_uid_t;

extern const ilrd_uid_t UIDBadUID;

/****************************************************************************
* 		
* Description: Creates a UID to the process that called it. the UID include PID 
	       of the process, timestamp, counter, and computers IP.
*		        
*   Arguments: None;
*		
*      Return: UID on success, UIDBadUID on failure.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

ilrd_uid_t UIDCreate(void);

/****************************************************************************
* 		
* Description: Finds out if two UID's are equal.
*		        
*   Arguments: uid1 - A UID to compare.
*	       uid2 - A UID to compare.
*		
*      Return: 1 if equal, 0 if not.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /* End of __ILRD_UID_H__ */
