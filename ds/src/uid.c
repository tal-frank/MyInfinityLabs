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
#include <arpa/inet.h>	/* struct sockaddr_in */
#include <pthread.h> /* mutex */

#include "uid.h"

#define COMP_SAME (0)

const ilrd_uid_t UIDBadUID = {0};


/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATIONS *************************/
/*-------------------------------------------------------------------------------*/

static size_t SetCounter(void);
static void SetIP(ilrd_uid_t* uid);
static pthread_mutex_t uid_mutex = PTHREAD_MUTEX_INITIALIZER;

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
			COMP_SAME    == memcmp(uid1.ip, uid2.ip, IPSIZE));
}


/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static size_t SetCounter(void)
{
	static size_t counter = 0;

	pthread_mutex_lock(&uid_mutex);
	++counter;
	pthread_mutex_unlock(&uid_mutex);

	return counter;
}

static void SetIP(ilrd_uid_t* uid)
{
	struct ifaddrs* ifa = {0};
	struct ifaddrs* ifa_runner = {0};
	struct sockaddr_in* ip_converter = NULL;

	if (ERROR == getifaddrs(&ifa))
	{
		*uid = UIDBadUID;
		return;
	}
		
	for (ifa_runner = ifa; NULL != ifa_runner; ifa_runner = ifa_runner->ifa_next)
	{
		if (NULL      != ifa_runner->ifa_addr            &&
		    AF_INET   == ifa_runner->ifa_addr->sa_family &&
		    COMP_SAME != strcmp(ifa_runner->ifa_name, "lo"))
		{
			ip_converter = (struct sockaddr_in*)ifa_runner;
			memcpy(uid->ip, (char*)&ip_converter->sin_addr, IPSIZE);
			freeifaddrs(ifa);
			return;
		}
	}
	
	if (NULL == ifa_runner)
	{
		*uid = UIDBadUID;
	}
	
	freeifaddrs(ifa);
}

