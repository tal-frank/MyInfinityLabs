
#include <string.h>
#include <stdlib.h>

#include "serialization.c"

#define FILE_NAME "binary_file.bin"


/************************************ HELP FUNCTIONS ************************************/

void Serialize(student_t* student, char* file_name)
{
	FILE* bin_file = fopen(file_name, "wb");
	
	if (NULL == bin_file)
	{
		printf("can not open the file\n");
		exit(1);
	}
	
	SaveStudentData(student, bin_file);
	fclose(bin_file);
}

void Deserialize(student_t* student, char* file_name)
{	
	FILE* bin_file = fopen(file_name, "rb");
	
	if (NULL == bin_file)
	{
		printf("can not open the file\n");
		exit(1);
	}
	
	LoadStudentData(student, bin_file);
	fclose(bin_file);
}

void print_student(student_t student, int num)
{
	printf("student %d first name is %s\n", 
		num, student.first_name);
	printf("student %d last name is %s\n", 
		num, student.last_name);
	printf("student %d math grade is %f\n", 
		num, student.grades.real_grades.math);
	printf("student %d physics grade is %f\n", 
		num, student.grades.real_grades.physics);
	printf("student %d computer science grade is %f\n", 
		num, student.grades.real_grades.computer_science);
	printf("student %d philosophy grade is %f\n", 
		num, student.grades.humanistic_grades.philosophy);
	printf("student %d history grade is %f\n", 
		num, student.grades.humanistic_grades.history);
	printf("student %d literature grade is %f\n", 
		num, student.grades.humanistic_grades.literature);
	printf("student %d sports grade is %f\n\n", 
		num, student.grades.sports);
}

/************************************ MAIN ************************************/


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

	char f_name_s1[MAX_NAME_SIZE] = "Some";
	char l_name_s1[MAX_NAME_SIZE] = "Body";


/********** INITIALIZE FIRST STUDENT **********/
	
	
	real_s1.math = 90;
	real_s1.physics = 79;
	real_s1.computer_science = 84;
	
	humanistic_s1.philosophy = 73;
	humanistic_s1.history = 95;
	humanistic_s1.literature = 67;
	
	grades_s1.humanistic_grades = humanistic_s1;
	grades_s1.real_grades = real_s1;
	grades_s1.sports = 88;
	
	student_1.grades = grades_s1;
	strcpy(student_1.first_name, f_name_s1);
	strcpy(student_1.last_name, l_name_s1);


/********** INITIALIZE SECOND STUDENT **********/
	
	real_s2.math = 0;
	real_s2.physics = 0;
	real_s2.computer_science = 0;
	
	humanistic_s2.philosophy = 0;
	humanistic_s2.history = 0;
	humanistic_s2.literature = 0;

	grades_s2.humanistic_grades = humanistic_s2;
	grades_s2.real_grades = real_s2;
	grades_s2.sports = 0;
	
	student_2.grades = grades_s2;
	

/********** SERIALIZE **********/


	Serialize(&student_1, FILE_NAME);
	Deserialize(&student_2, FILE_NAME);


/********** PRINT RESAULTS **********/

	print_student(student_1, 1);
	print_student(student_2, 2);

	
	
	return 0;
}














