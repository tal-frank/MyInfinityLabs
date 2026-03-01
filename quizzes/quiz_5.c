#include <stddef.h>
#include <stdio.h>



struct stock_val
{
	int buy;
	int sell;
	int max_profit;
};


struct stock_val stock_prof(int arr[], size_t size)
{
	size_t i;
	struct stock_val stock;
	int buy;
	
	buy = 0;
	stock.buy = 0;
	stock.sell = 0;
	stock.max_profit = 0;
	
	for (i = 1; i < size; ++i)
	{
		if (arr[stock.buy] >= arr[i])
		{
			buy = i;
		}
		else
		{
			if (arr[i] - arr[buy] > stock.max_profit)
			{
				stock.buy = buy;
				stock.sell = i;
				stock.max_profit = arr[stock.sell] -arr[stock.buy];
			}
		}		
	}
	return stock;
}




int main()
{
	struct stock_val stock;
	int arr[] = {38, 72, 33, 12, 67, 58, 49, 84, 91, 2, 29, 42};
	
	stock = stock_prof(arr, 12);
	printf("max profit possible = %d\n" , stock.max_profit);
	printf("buy hour is %d:00 and sell hour is %d:00\n" , stock.buy, stock.sell);

	return 0;
}




