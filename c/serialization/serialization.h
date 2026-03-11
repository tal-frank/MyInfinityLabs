
#ifndef __SERIALIZE_STRUCTS_H__
#define __SERIALIZE_STRUCTS_H__

/************************************ Standard libraries ********************************/
#include <stdio.h>


/************************************ Define statments *********************************/
#define MAX_NAME_SIZE 30


/************************************ Structs statments ***********************************/
typedef struct Humanistic_grades
{
	float philosophy;
	float history;
	float literature;
} humanistic_t;

typedef struct Real_grades
{
	float math;
	float physics;
	float computer_science;
} real_t;

typedef struct Grades
{
	humanistic_t humanistic_grades;
	real_t real_grades;
	float sports;
} grades_t;

typedef struct Student
{
	grades_t grades;
	char first_name[MAX_NAME_SIZE];
	char last_name[MAX_NAME_SIZE];
} student_t;

/************************************ Functions declerations ************************************/

int SaveStudentData(student_t* student, FILE* file_p);

int LoadStudentData(student_t* student, FILE* file_p);


#endif /*End of __SERIALIZE_STRUCTS_H__*/

