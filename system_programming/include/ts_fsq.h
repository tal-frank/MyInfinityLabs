#ifndef __TS_FSQUEUE_H__
#define __TS_FSQUEUE_H__

/********************************************************* Standard libraries */

#include <stddef.h>	/* size_t */

/******************************************************************* Typedefs */

typedef struct TSFSQueueu ts_fsq_t;

/************************************************************** API functions */

/**************************************************************** FunctionName *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
ts_fsq_t* FSQCreate(size_t capacity, size_t element_size);

void FSQDestroy(ts_fsq_t* fsq);

void FSQEnqueue(ts_fsq_t* fsq, void* src);

void FSQDequeue(ts_fsq_t* fsq, void* dest);

size_t FSQSize(const ts_fsq_t* fsq);

#endif/********************************************** End of __TS_FSQUEUE_H__ */