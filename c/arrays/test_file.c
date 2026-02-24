#include <stdio.h>
#include <string.h>
#include <stddef.h>

void PrintTypeLength()
{
	printf("char : %lu\n" , sizeof(char));
	printf("signed char : %lu\n" , sizeof(signed char));
	printf("unsigned char : %lu\n" , sizeof(unsigned char));
	printf("short : %lu\n" , sizeof(short));
	printf("short int : %lu\n" , sizeof(short int));
	printf("signed short : %lu\n" , sizeof(signed short));
	printf("signed short int : %lu\n" , sizeof(signed short int));
	printf("unsigned short : %lu\n" , sizeof(unsigned short));
	printf("unsigned short int : %lu\n" , sizeof(unsigned short int));
	printf("int : %lu\n" , sizeof(int));
	printf("signed : %lu\n" , sizeof(signed));
	printf("signed int : %lu\n" , sizeof(signed int));
	printf("unsigned : %lu\n" , sizeof(unsigned));
	printf("unsigned int : %lu\n" , sizeof(unsigned int));
	printf("long : %lu\n" , sizeof(long));
	printf("long int : %lu\n" , sizeof(long int));
	printf("signed long : %lu\n" , sizeof(signed long));
	printf("signed long int : %lu\n" , sizeof(signed long int));
	printf("unsigned long : %lu\n" , sizeof(unsigned long));
	printf("unsigned long int : %lu\n" , sizeof(unsigned long int));
/*	printf("long long : %lu\n" , sizeof(long long));
	printf("long long int : %lu\n" , sizeof(long long int));
	printf("signed long long : %lu\n" , sizeof(signed long long));
	printf("signed long long int : %lu\n" , sizeof(signed long long int));
	printf("unsigned long long : %lu\n" , sizeof(unsigned long long));
	printf("unsigned long long int : %lu\n" , sizeof(unsigned long long int)); */
	printf("float : %lu\n" , sizeof(float));
	printf("double : %lu\n" , sizeof(double));
	printf("long double : %lu\n" , sizeof(long double));
}

void foo(int a[], int size)
{
	size_t size_func_arr;
	int i = 0;
	
	for (i = 0; i<size; ++i)
	{
		a[i] = i * 2;
	}
	size_func_arr = sizeof(a);
	printf("sizeof size_arr in foo= %zu\n", size_func_arr);
}


int main(int argc, char** argv, char** envp)
{
	size_t size_str;
	int len_str;
	size_t size_arr;
	char str[] = "welcome";
	int arr[10] = {0};
	foo(arr, 10); 

	size_str = sizeof(str);
	len_str = strlen(str);
	size_arr = sizeof(arr);

	
	printf("sizeof str = %zu\n", size_str);
	printf("length of str = %d\n" , len_str);
	printf("sizeof size_arr = %zu\n", size_arr);
	
	PrintTypeLength();

	return (0);
	


	
}
