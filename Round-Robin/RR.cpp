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
void EnqueueReady(int);
void DequeueReady();

int main()
{
	InitProcesses(Procs);
	for(int Index = 0; Index < PROC_COUNT; ++Index)
	{
		EnqueueReady(Index);
	}

	// Main loop
	for (Process* proc = ReadyQueue[0]; proc != nullptr; proc = ReadyQueue[0])
	{

		DequeueReady();
	}
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

void EnqueueReady(int Index)
{
	++QueueLast;
	if(QueueLast >= PROC_COUNT)
	{
		printf("Queue overload");
		exit(-1);
	}

	ReadyQueue[QueueLast] = &Procs[Index];
}

void DequeueReady()
{
	for(int Index = 1; Index < QueueLast + 1; ++Index)
	{
		ReadyQueue[Index - 1] = ReadyQueue[Index];
	}
	for (int Index = QueueLast; Index < PROC_COUNT; ++Index)
	{
		ReadyQueue[Index] = nullptr;
	}
	--QueueLast;
}
