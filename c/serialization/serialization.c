/**********************
* ws10_serialized_structs
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update:
**********************/
#include "serialization.h"

/************************************ FUNCTIONS DECLERATIONS ************************************/

void serialize(student_t* student, char* file_name);
void Deserialize(student_t* student, char* file_name);


/************************************ SERIALIZE FUNCTIONS ************************************/

int SaveStudentData(student_t* student, FILE* file_p)
{	
	fwrite(&student->grades.humanistic_grades.philosophy, 
		sizeof(float), 1, file_p);
	fwrite(&student->grades.humanistic_grades.history, 
		sizeof(float), 1, file_p);
	fwrite(&student->grades.humanistic_grades.literature, 
		sizeof(float), 1, file_p);
		
	fwrite(&student->grades.real_grades.math, 
		sizeof(float), 1, file_p);
	fwrite(&student->grades.real_grades.physics, 
		sizeof(float), 1, file_p);
	fwrite(&student->grades.real_grades.computer_science, 
		sizeof(float), 1, file_p);
		
	fwrite(&student->grades.sports, 
		sizeof(float), 1, file_p);
		
	fwrite(student->first_name, sizeof(char), 
		MAX_NAME_SIZE, file_p);
	fwrite(student->last_name, sizeof(char), 
		MAX_NAME_SIZE, file_p);
				
	return 0;
}


int LoadStudentData(student_t* student, FILE* file_p)
{	
	fread(&student->grades.humanistic_grades.philosophy, 
		sizeof(float), 1, file_p);
	fread(&student->grades.humanistic_grades.history, 
		sizeof(float), 1, file_p);
	fread(&student->grades.humanistic_grades.literature, 
		sizeof(float), 1, file_p);
		
	fread(&student->grades.real_grades.math, 
		sizeof(float), 1, file_p);
	fread(&student->grades.real_grades.physics, 
		sizeof(float), 1, file_p);
	fread(&student->grades.real_grades.computer_science, 
		sizeof(float), 1, file_p);
		
	fread(&student->grades.sports, 
		sizeof(float), 1, file_p);
		
	fread(student->first_name, sizeof(char), 
		MAX_NAME_SIZE, file_p);
	fread(student->last_name, sizeof(char), 
		MAX_NAME_SIZE, file_p);
	
	return 0;
}


















