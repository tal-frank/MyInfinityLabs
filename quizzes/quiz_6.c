#include <string.h>
#include <stdio.h>

int IsRotation(char* s1, char* s2)
{
	size_t i;
	char* s1_init = s1;
	char* s2_init = s2;
	int is_rotation = 0;
	
	if(strlen(s1) != strlen(s2))
	{
		return is_rotation;
	}
	
	for (i = 0; i < strlen(s1); ++i)
	{
		while ('\0' != *s1)
		{
			if ('\0' == *s2)
			{
				s2 = s2_init;
			}
			if (*s1 == *s2)
			{
				++s1; ++s2;
				is_rotation = 1;
				continue;
			}
			is_rotation = 0;
			break;
		}
		if (is_rotation)
		{
			return is_rotation;
		}
		s1 = s1_init;
		s2 = s2_init + i + 1;
	}
	return is_rotation;
}

int main ()
{
	int is_rotation;
	char str1[] = "123456";
	char str2[] = "345612";
	
	is_rotation = IsRotation(str1, str2);
	
	printf("is_rotation = %d\n", is_rotation);
	
	return 0;	
}







