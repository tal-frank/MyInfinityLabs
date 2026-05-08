
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include <string.h>

#include "uid.h"


static void PrintUID(ilrd_uid_t uid)
{
	struct in_addr IP = {0};
	
	printf("UID --- PID        = %d\n", uid.pid);
	printf("UID --- time       = %s", ctime(&uid.time));
	printf("UID --- counter    = %ld\n", uid.counter);
	
	assert(NULL != uid.ip);
	memcpy(&IP, uid.ip, sizeof(IP));
	printf("UID --- IP Address = %s\n", inet_ntoa(IP));	
}


int main ()
{
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	
	uid1 = UIDCreate();
	uid2 = UIDCreate();
	sleep(2);
	uid3 = UIDCreate();
	
	PrintUID(uid1);
	printf("\n");
	PrintUID(uid2);
	printf("\n");
	PrintUID(uid3);
	printf("\n");
	PrintUID(UIDBadUID);
	printf("\n");
	
	if (UIDIsEqual(uid1, uid1))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	if (UIDIsEqual(uid2, uid2))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	if (UIDIsEqual(uid3, uid3))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	if (!UIDIsEqual(uid1, uid2))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	if (!UIDIsEqual(uid1, uid3))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	if (!UIDIsEqual(uid2, uid3))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}	
	return 0;
}
