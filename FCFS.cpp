#include<stdio.h>
int main()
{
	int pid[15];
	int bt[15];
	int n,i;
	printf("enter the no.of processors:");
	scanf("%d",&n);
	printf("enter the process id of all the processes:");
	for(i=0;i<n;i++)
	{
		scanf("%d",&pid[i]);
	}
	printf("enter burst time of all the processes:");
	for(i=0;i<n;i++)
	{
		scanf("%d",&bt[i]);
	}
	int wt[i];
	wt[0]=0;
	for(i=1;i<n;i++)
	{
		wt[i]=bt[i-1]+wt[i-1];
	}
	printf("process id burst time waiting time turnaround time\n");
	float twt=0.0;
	float tat=0.0;
	for(i=0;i<n;i++)
	{
		printf("%d\t\t",pid[i]);
		printf("%d\t\t",bt[i]);
		printf("%d\t\t",wt[i]);
		printf("%d\t\t",bt[i]+wt[i]);
		printf("\n");
		twt+=wt[i];
		tat+=(wt[i]+bt[i]);
	}
	float att,awt;
	awt=twt/n;
	att=tat/n;
	printf("average waiting time=%f\n",awt);
	printf("average turnaround time=%f",att);
}
