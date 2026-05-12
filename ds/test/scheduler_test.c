#include <time.h>
#include <stdio.h>

#include "scheduler.h"
#include "task.h" /* task API */

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

typedef struct run_n_times
{
	sched_t* sched;
	ilrd_uid_t uid;
	size_t count;
	char* str;
}run_n_times_t;

static int Stop(void* param_sched)
{
	sched_t* sched = (sched_t*)param_sched;
	SchedStop(sched);
	return 0;
}

static int func(void* param)
{
	char* str = (char*)param;
	printf("%s\n", str);
	return 0;
}

static int func_remove(void* param)
{
	run_n_times_t* rnt = (run_n_times_t*)param;
	printf("%s\n", rnt->str);
	++rnt->count;
	if (3 == rnt->count)
	{
		SchedTaskRemove(rnt->sched, rnt->uid);
	}
	return 0;
}

void TestEmptyAdd(void)
{
	sched_t* sched = SchedCreate();
	time_t current_time = 0;
	time(&current_time);
	
	printf(CYAN "IS EMPTY" RESET_COLOR " TEST\n");
	if (!SchedIsEmpty(sched))
	{
		printf("not empty after create.\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		SchedDestroy(sched);
		return;
	}
	printf("empty after create\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	SchedTaskAdd(sched, 10, current_time + 5, func, NULL, "five sec");
	
	if (SchedIsEmpty(sched))
	{
		printf("empty after add task.\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		SchedDestroy(sched);
		return;
	}
	printf("not empty after add task\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	printf(CYAN "ERASE/COUNT" RESET_COLOR " TEST\n");
	if (1 != SchedCount(sched))
	{
		printf("did not insert task \n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		SchedDestroy(sched);
		return;
	}
	printf("inserted task\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	SchedDestroy(sched);
	
}

void TestCountClear(void)
{
	sched_t* sched = SchedCreate();
	time_t current_time = 0;
	time(&current_time);
	SchedTaskAdd(sched, 10, current_time + 5, func, NULL, "five sec");
	SchedTaskAdd(sched, 4, current_time + 2, func, NULL, "two sec");
	SchedTaskAdd(sched, 2, current_time + 10, func, NULL, "ten sec");
	
	if (3 != SchedCount(sched))
	{
		printf("did not insert tasks \n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		SchedDestroy(sched);
		return;
	}
	printf("inserted 3 tasks\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	SchedClear(sched);
	
	printf(CYAN "CLEAR" RESET_COLOR " TEST\n");
	if (!SchedIsEmpty(sched))
	{
		printf("not empty after clear.\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		SchedDestroy(sched);
		return;
	}
	printf("empty after clear\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	SchedDestroy(sched);
}


void TestRemove()
{
	sched_t* sched = SchedCreate();
	time_t current_time = 0;
	ilrd_uid_t uid = UIDBadUID;
	time(&current_time);
	SchedTaskAdd(sched, 10, current_time + 5, func, NULL, "five sec");
	SchedTaskAdd(sched, 4, current_time + 2, func, NULL, "two sec");
	SchedTaskAdd(sched, 2, current_time + 10, func, NULL, "ten sec");
	uid = SchedTaskAdd(sched, 1, current_time + 15, func, NULL, "fifteen sec");
	printf(CYAN "REMOVE" RESET_COLOR " TEST\n");
	SchedTaskRemove(sched, uid);
	if (3 != SchedCount(sched))
	{
		printf("did not remove task \n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		SchedDestroy(sched);
		return;
	}
	printf("removed task\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	SchedDestroy(sched);
}

void TestRun(void)
{
	sched_t* sched = SchedCreate();
	time_t current_time = 0;
	printf(CYAN "RUNNING CHECK\n" RESET_COLOR);
	time(&current_time);
	SchedTaskAdd(sched, 10, current_time + 10, func, NULL, RED "ten sec" RESET_COLOR);
	SchedTaskAdd(sched, 4, current_time + 4, func, NULL, GREEN "four sec" RESET_COLOR);
	SchedTaskAdd(sched, 5, current_time + 5, func, NULL, CYAN "five sec" RESET_COLOR);
	SchedTaskAdd(sched, 2, current_time + 2, func, NULL, "two sec");
	SchedTaskAdd(sched, 6, current_time + 6, func, NULL, "six sec");
	SchedTaskAdd(sched, 0, current_time + 11, Stop, NULL, sched);
	
	
	SchedRun(sched);
	SchedDestroy(sched);
}

void TestRunWithRemove(void)
{
	sched_t* sched = SchedCreate();
	time_t current_time = 0;
	ilrd_uid_t uid = {0};
	run_n_times_t rnt = {0};
	printf(CYAN "RUNNING WITH REMOVAL CHECK\n" RESET_COLOR);
	time(&current_time);
	SchedTaskAdd(sched, 10, current_time + 10, func, NULL, RED "ten sec" RESET_COLOR);
	SchedTaskAdd(sched, 4, current_time + 4, func, NULL, GREEN "four sec" RESET_COLOR);
	SchedTaskAdd(sched, 5, current_time + 5, func, NULL, CYAN "five sec" RESET_COLOR);
	uid = SchedTaskAdd(sched, 2, current_time + 2, func_remove, NULL, &rnt);
	SchedTaskAdd(sched, 6, current_time + 6, func, NULL, "six sec");
	SchedTaskAdd(sched, 0, current_time + 13, Stop, NULL, sched);
	
	rnt.sched = sched;
	rnt.uid = uid;
	rnt.str = "two sec";
	rnt.count = 0;
	
	SchedRun(sched);
	SchedDestroy(sched);
}


int main()
{
	printf("\n");
	TestEmptyAdd();
	TestCountClear();
	TestRemove();
	TestRun();
	printf("\n");
	TestRunWithRemove();
	
	return 0;
}
