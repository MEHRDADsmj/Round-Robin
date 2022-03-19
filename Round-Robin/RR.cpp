#include <cstdio>
#include <cstdlib>
#include <cstring>

#define PROC_COUNT 5
#define TIME_SLICE 1

typedef struct
{
	int ID;
	float BurstTime;
	char Name[10];
} Process;

Process Procs[PROC_COUNT];

Process* ReadyQueue[PROC_COUNT];
int QueueLast = -1;

void InitProcesses(Process*);

int main()
{
	printf("Hello world!");
	return 0;
}

void InitProcesses(Process* procs)
{
	procs[0].BurstTime = 2.0f;
	procs[1].BurstTime = 2.0f;
	procs[2].BurstTime = 3.0f;
	procs[3].BurstTime = 1.0f;
	procs[4].BurstTime = 0.5f;

	for (int Index = 0; Index < PROC_COUNT; ++Index)
	{
		procs[Index].ID = Index;
		strcpy_s(procs[Index].Name, "Process ");
		char Num[2];
		_itoa_s(Index, Num, 10);
		strcat_s(procs[Index].Name, Num);
	}
}