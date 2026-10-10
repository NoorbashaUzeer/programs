#include<stdio.h>
#include<conio.h>
int n ,capacity;
int weight[100],profit[100];
int maxprofit =0;
int bestselection[100];
int currentselection[100];
void knapsack(int i ,int currentweight,int currentprofit)
{
	int j;
	if(currentweight > capacity)
	return;
	if(i==n)
	{
		if(currentprofit > maxprofit)
		{
			maxprofit = currentprofit;
			for(j=0;j<n;j++)
			bestselection[j] = currentselection[j];
			}
			return;
	}
	currentselection[i]=1;
	knapsack(i+1,currentweight+weight[i],currentprofit+profit[i]);
	currentselection[i]=0;
	knapsack(i+1,currentweight,currentprofit);
}
void main()
{
	int i;
	int totalweight =0;
	printf("enter the number of items:");
	scanf("%d",&n);
	printf("\nEnter the weight and profit of each item:\n");
	for(i=0;i<n;i++)
	{
		printf("\n Item %d weight:",i+1);
		scanf("%d",&weight[i]);
		printf("Item %d profit :",i+1);
		scanf("%d",&profit[i]);
	}
	printf("\n Enter the capacity of the knapsack:");
	scanf("%d",&capacity);
	for(i=0;i<n;i++)
	currentselection[i]=0;
	knapsack(0,0,0);
	printf("\n\n-------------------------------");
	printf("\n Maximunm profits = %d ",maxprofit);
	printf("\n\n items inserted int he bag:");
	for(i=0;i<n;i++)
	{
		if (bestselection[i]==1)
		{
			printf("\n item %d (weigth =%d,profit =%d )",i+1 ,weight[i],profit[i]);
			totalweight = totalweight+weight[i];
		}
	}
	printf("\n\n Totalweight = %d ",totalweight);
	printf("\n------------------------------");
	getch();
}