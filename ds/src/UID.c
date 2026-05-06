/**********************
* UID
* Author: Tal Frank
* Reviewer: Ori Yoseph
* Last update: 06/05/2026
**********************/

#include <unistd.h> /* getpid */
#include <ifaddrs.h> /* getifaddrs ,  freeifaddrs */
#include <time.h> /* time , ctime */
#include <string.h> /* memcpy , memcmp */

#include "UID.h"

#define IS_EQUAL (1)
#define IP_SIZE (14)

const ilrd_uid_t UIDBadUID = {0};


/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATIONS *************************/
/*-------------------------------------------------------------------------------*/

static size_t SetCounter(void);
static void SetIP(ilrd_uid_t* uid);

typedef enum
{
	ERROR = -1,
	SUCCESS
}status_t;


/*--------------------------------------------------------*/
/************************* CREATE *************************/
/*--------------------------------------------------------*/

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid = {0};
	
	uid.pid = getpid();
	uid.time = time(NULL);
	if (ERROR == uid.time)
	{
		return UIDBadUID;
	}

	uid.counter = SetCounter();
	SetIP(&uid);
	
	return uid;
}


/*----------------------------------------------------------*/
/************************* IS EQUAL *************************/
/*----------------------------------------------------------*/

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.pid     == uid2.pid     &&
		uid1.time    == uid2.time    &&
		uid1.counter == uid2.counter &&
		0            == memcmp(uid1.ip, uid2.ip, IP_SIZE)) 
		? IS_EQUAL : !IS_EQUAL;
}


/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static size_t SetCounter(void)
{
	static size_t counter = 0;
	++counter;
	return counter;
}

static void SetIP(ilrd_uid_t* uid)
{
	struct ifaddrs* ifa = NULL;
	struct ifaddrs* tmp = NULL;

	if (ERROR == getifaddrs(&ifa))
	{
		*uid = UIDBadUID;
		return;
	}
		
	for (tmp = ifa; NULL != tmp; tmp = tmp->ifa_next)
	{
		if (NULL    != tmp->ifa_addr            &&
		    AF_INET == tmp->ifa_addr->sa_family)
		{
			memcpy(uid->ip, ifa->ifa_addr, IP_SIZE);
			freeifaddrs(ifa);
			return;
		}
	}
	
	if (NULL == tmp)
	{
		*uid = UIDBadUID;
	}
	
	freeifaddrs(ifa);

}

