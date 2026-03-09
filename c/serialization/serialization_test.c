/**********************
* ws10_serialized_structs
* Author: Tal Frank
* Reviewer:
* Last update:
**********************/

#include <string.h>
#include <stdlib.h>
#include "serialization.c"

int main()
{
	student_t student_1;
	grades_t grades_s1;
	real_t real_s1;
	humanistic_t humanistic_s1;
	student_t student_2;
	grades_t grades_s2;
	real_t real_s2;
	humanistic_t humanistic_s2;
	char* bin_file_name = "binary_file.bin";
	char f_name_s1[30] = "Some";
	char l_name_s1[30] = "Body";


/********** INITIALIZE FIRST STUDENT **********/
	
	real_s1.math = 90;
	real_s1.physics = 79;
	real_s1.computer_science = 84;
	
	humanistic_s1.philosophy = 73;
	humanistic_s1.history = 95;
	humanistic_s1.literature = 67;
	
	grades_s1.humanistic_grades = &humanistic_s1;
	grades_s1.real_grades = &real_s1;
	grades_s1.sports = 88;
	
	student_1.grades = &grades_s1;
	strcpy(student_1.first_name, f_name_s1);
	strcpy(student_1.last_name, l_name_s1);


/********** INITIALIZE SECOND STUDENT **********/
	
	real_s2.math = 0;
	real_s2.physics = 0;
	real_s2.computer_science = 0;
	
	humanistic_s2.philosophy = 0;
	humanistic_s2.history = 0;
	humanistic_s2.literature = 0;

	grades_s2.humanistic_grades = &humanistic_s2;
	grades_s2.real_grades = &real_s2;
	grades_s2.sports = 0;
	
	student_2.grades = &grades_s2;
	

/********** SERIALIZE **********/

	Serialize(&student_1, bin_file_name);
	Deserialize(&student_2, bin_file_name);


/********** PRINT RESAULTS **********/

	printf("student 2 first name is %s\n", student_2.first_name);
	printf("student 2 last name is %s\n", student_2.last_name);
	printf("student 2 math grade is %f\n", student_2.grades->real_grades->math);
	printf("student 2 physics grade is %f\n", student_2.grades->real_grades->physics);
	printf("student 2 computer science grade is %f\n", student_2.grades->real_grades->computer_science);
	printf("student 2 philosophy grade is %f\n", student_2.grades->humanistic_grades->philosophy);
	printf("student 2 history grade is %f\n", student_2.grades->humanistic_grades->history);
	printf("student 2 literature grade is %f\n", student_2.grades->humanistic_grades->literature);
	printf("student 2 sports grade is %f\n", student_2.grades->sports);
	
	return 0;
}














