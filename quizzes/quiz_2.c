#include <stdio.h>
#include <string.h>
#include <ctype.h>

void TF (int num)
{
	int i;
	int is_devided = 0;
	for(i = 0; i < num; ++i)
	{
		is_devided = 0;
		if (i % 3 == 0)
		{
			printf("T"); 
			is_devided = 1;
		}
		if (i % 5 == 0)
		{
			printf("F");
			is_devided = 1;
		}
		if (is_devided == 0)
		{
			printf("%d", i);
		}
		printf("\n");
	}
}

char* reverse_string (char* str)
{
	int i;
	int len;
	char rev_str;
	
	len = strlen(str);
	rev_str = (str + len - 1);

	for (i = 0; i < len / 2; ++i)
	{
		*str = rev_str;
		++str; --rev_str;
	}
	return rev_str;
}


int main()
{
	char* str = "HellO woRld";	
	
	reverse_string(str);
	TF(11);
	
	printf("%s", str);
	

	return 0;
}













