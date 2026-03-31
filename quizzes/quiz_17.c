#include <stdio.h>


static int ch_cnt[256] = {0};

void NumOccur(char insert)
{
	int max = 0;
	int i = 0;
	char ch = 0;
	
	if ('0' == insert)
	{
		for(i = 0; i < 256; ++i)
		{
			if (max < ch_cnt[i])
			{
				ch = (char)i;
				max = ch_cnt[i];
			}
			ch_cnt[i] = 0;
		}
		printf("the char %c occurs %d times\n", ch, max);
	}
	ch_cnt[(int)insert] += 1;
}





int main()
{	
	NumOccur('g');
	NumOccur('3');
	NumOccur('k');
	NumOccur('1');
	NumOccur('3');
	NumOccur('6');
	NumOccur('1');
	NumOccur('3');
	NumOccur('t');
	NumOccur('T');
	NumOccur('3');
	NumOccur('1');
	NumOccur('c');
	NumOccur('A');	
	NumOccur('t');
	NumOccur('3');
	NumOccur('Y');
	NumOccur('1');
	NumOccur('k');
	NumOccur('1');
	NumOccur('q');
	NumOccur('z');
	NumOccur('%');
	NumOccur('#');
	NumOccur('g');
	NumOccur('3');
	NumOccur('1');
	NumOccur('0');
	NumOccur('5');
	NumOccur('2');
	NumOccur('5');
	NumOccur('g');
	NumOccur('0');
	
	return 0;
}
