#include <cstdio>
#include <cstdlib>
#include <cstring>

#define PROC_COUNT 5
#define TIME_SLICE 1

typedef struct
{
	int ID;
	float BurstTime;
	float RemainingBurst;
	float OutTime;
	// InTime is considered 0.0f for all processes
	char Name[10];
} Process;

Process Procs[PROC_COUNT];

Process* ReadyQueue[PROC_COUNT];
int QueueLast = -1;

void InitProcesses(Process*);
void EnqueueReady(int);
void DequeueReady();
void ConsumeProcess(Process*, float);

int main()
{
	InitProcesses(Procs);
	for(int Index = 0; Index < PROC_COUNT; ++Index)
	{
		EnqueueReady(Index);
	}

	float WaitingTime[PROC_COUNT];
	float TurningTime[PROC_COUNT];
	WaitingTime[0] = 0.0f;
	float AWT = 0.0f;
	float ATT = 0.0f;

	// Main loop
	float Time = 0.0f;
	for (Process* proc = ReadyQueue[0]; proc != nullptr; proc = ReadyQueue[0])
	{
		DequeueReady();
		Time += TIME_SLICE;
		ConsumeProcess(proc, Time);
	}

	for (int Index = 0; Index < PROC_COUNT; ++Index)
	{
		Index == 0 ? WaitingTime[Index] = 0.0f : WaitingTime[Index] = WaitingTime[Index - 1] + Procs[Index - 1].BurstTime + Procs[Index - 1].OutTime;
		TurningTime[Index] = WaitingTime[Index] + Procs[Index].BurstTime + Procs[Index].OutTime;
		AWT += WaitingTime[Index];
		ATT += TurningTime[Index];
	}

	AWT /= PROC_COUNT;
	ATT /= PROC_COUNT;

	for (int Index = 0; Index < PROC_COUNT; ++Index)
	{
		printf("%s\tWT = %.2f | TT = %.2f\n", Procs[Index].Name,
			WaitingTime[Index], TurningTime[Index]);
	}
	printf("AWT = %f\nATT = %f\n", AWT, ATT);
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
		procs[Index].RemainingBurst = procs[Index].BurstTime;
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

void ConsumeProcess(Process* proc, float Time)
{
	proc->RemainingBurst -= TIME_SLICE;
	if (proc->RemainingBurst > 0.0f)
	{
		EnqueueReady(proc->ID);
	}
	else
	{
		proc->OutTime = Time;
	}
}
