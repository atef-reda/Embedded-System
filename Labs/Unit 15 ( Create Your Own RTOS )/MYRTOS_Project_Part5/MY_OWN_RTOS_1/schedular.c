/*
 * schedular.c
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */




#include "MYRTOS_FIFO.h"
#include "string.h"

struct {
	Task_ref* OsTasks[20];
	unsigned int *_S_MSP_Task;
	unsigned int *_E_MSP_Task;
	unsigned int *_PSP_Task_Locator;
	unsigned int NoOfActiveTasks;
	Task_ref *CurrentTask;
	Task_ref *NextTask;
	enum{
		OsSuspend,
		OsRuinning
	}OsModeID;
} Os_Control;

typedef enum
{
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_TaskWaitingTime,
}SVC_ID;


void MYRTOS_idleTask();
void MyRTOS_Create_TaskStack(Task_ref* Tref);
void MYRTOS_Os_SVC_Set(SVC_ID ID);
FIFO_Buf_t Ready_QUEUE ;
Task_ref *Ready_QUEUE_FIFO[100];
Task_ref MYRTOS_IdleTask;
void bubbleSort()
{
	int i,j,n;
	n=Os_Control.NoOfActiveTasks;
	Task_ref* Temp;

	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(Os_Control.OsTasks[j]->Priority>Os_Control.OsTasks[j+1]->Priority)
			{
				Temp=Os_Control.OsTasks[j];
				Os_Control.OsTasks[j]=Os_Control.OsTasks[j+1];
				Os_Control.OsTasks[j+1]=Temp;
			}
		}
	}
}
void MYRTOS_Update_Sch_Table() {
	Task_ref* Temp;
	int i=0;
	Task_ref* Ptask;
	Task_ref* PnextTask;
	//1- bubble sort SchTable OS_Control-> OSTASKS[20] (priority high then low)
	bubbleSort();
	//2- free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE,&Temp /* pointer to pointer */)!=FIFO_EMPTY);
	//3- update ready queue


	while(i<Os_Control.NoOfActiveTasks)   //@@@ note i'm  change in
	{
		Ptask=Os_Control.OsTasks[i];
		PnextTask=Os_Control.OsTasks[i+1];

		if(Ptask->Task_State!=Suspend)    //@@@ note :- why !=Suspend not ==Waiting
		{

			//in case we reached to the end of avaliable OSTASKS
			if(PnextTask->Task_State==Suspend)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State=Ready;
				break;
			}
			//	if the Ptask priority > nexttask then (lowest number is meaning higher priority)
			if(Ptask->Priority<PnextTask->Priority)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State = Ready;
				break;
			} else if (Ptask->Priority == PnextTask->Priority) {
				//	if the Ptask priority == nexttask then
				//		push Ptask to ready state
				//	And make the ptask = nexttask  and nexttask++
				//  =>> this acquire above update i=>i++ as not break in this if()
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State = Ready;
			} else if (Ptask->Priority > PnextTask->Priority) {
				//not allowed to happen as we already reordered it by bubble sort
				break;
			}
		}
		i++;
	}
}
//handler mode from scv_handler
void Decide_WhatNext()
{
	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if((Ready_QUEUE.counter==0) && Os_Control.CurrentTask!=Suspend)
	{
		Os_Control.CurrentTask->Task_State = Ruinning;
		//add the current task again(round robin)
		FIFO_enqueue(&Ready_QUEUE, Os_Control.CurrentTask);
		Os_Control.NextTask = Os_Control.CurrentTask;

	} else {
		FIFO_dequeue(&Ready_QUEUE, &Os_Control.NextTask);
		Os_Control.NextTask->Task_State = Ruinning;

		//update Ready queue (to keep round robin Algo. happen)
		if (Os_Control.CurrentTask->Priority == Os_Control.NextTask->Priority
				&& Os_Control.CurrentTask->Task_State != Suspend) {

			FIFO_enqueue(&Ready_QUEUE, Os_Control.CurrentTask);
			Os_Control.CurrentTask->Task_State = Ready;
		}
	}
}
//svc_handler (call)==> OS_SVC_Service so that in handler mode
  void OS_SVC_Service(int *StackFramePointer)
  {
  	//os_svc_set stack -> r0 -> argument0 = StackFramePointer
  	//os_svc_set stack r0,r1,r2,r3,r12,lr,pc,xpsp
  	unsigned char svc_number;

  	svc_number=((unsigned char *)StackFramePointer[6])[-2];

  	switch (svc_number) {
  	case SVC_ActivateTask:
  	case SVC_TerminateTask:
  		//Update sch table , ready queue
  		MYRTOS_Update_Sch_Table();
  		//if os in running state
  	    if(Os_Control.OsModeID==OsRuinning)
  	    {
  	    	if(strcmp(Os_Control.CurrentTask->Task_Name,"idleTask")!=0)
  	    	{
  	    		//decide what next
  	    		Decide_WhatNext();
  	    		//trigger pend_sv
  	    		trigger_OS_PendSV();
  	    	}
  	    }


  		break;
  	case SVC_TaskWaitingTime:
  		MYRTOS_Update_Sch_Table();
  		break;
  }

  }

  //thread mode
  void MYRTOS_Os_SVC_Set(SVC_ID ID)
   {
  	switch (ID) {
  	case SVC_ActivateTask:
  		__asm("svc #0x00");
  		break;
  	case SVC_TerminateTask:
  		__asm("svc #0x01");
  		break;
  	case SVC_TaskWaitingTime:
  		__asm("svc #0x02");
  		break;
  }
  }

  unsigned char PendSV_Led;

  __attribute ((naked)) void PendSV_Handler() {
	  PendSV_Led^=1;
	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0
	OS_GET_PSP(Os_Control.CurrentTask->Current_PSP);

	//using this Current_PSP (Pointer) tp store (R4 to R11)
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R4 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R5 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R6 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R7 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R8 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R9 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R10 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,R11 ": "=r"(*(Os_Control.CurrentTask->Current_PSP)));

	//save the current Value of PSP
	//already saved in Current_PSP

	//====================================
	//Restore the Context of the Next Task
	//====================================
	if (Os_Control.NextTask != NULL) {
		Os_Control.CurrentTask = Os_Control.NextTask;
		Os_Control.NextTask = NULL;
	}

	__asm volatile("mov R11,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R10,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R9,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R8,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R7,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R6,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R5,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov R4,%0"::"r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;

	//update PSP and exit
	OS_SET_PSP(Os_Control.CurrentTask->Current_PSP);
    __asm volatile("BX LR");
}











void MYRTOS_Create_MainStack(void)
{
	Os_Control._S_MSP_Task=&_estack;
	Os_Control._E_MSP_Task=(unsigned int*)((unsigned int)Os_Control._S_MSP_Task-(unsigned int)Main_Stack_Size);
	//aligned 8 byte
	Os_Control._PSP_Task_Locator=(unsigned int*)((unsigned int)Os_Control._E_MSP_Task-8);

	//if(_E_MSP_Task<&_eheap)  // error: excedded the avaliable size

}
MYRTOS_ErrorID MYRTOS_Init()
{
	MYRTOS_ErrorID error=NO_ERROR;

	//Update Os Mode (OsSuspend)
	Os_Control.OsModeID=OsSuspend;
	//Specify The main Stack For Os
	MYRTOS_Create_MainStack();


	//Create Os Ready Queue
	if (FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) != FIFO_NO_ERROR) {
		error += Ready_Queue_init_error;
	}
	//Configure Idel Task
    stpcpy(MYRTOS_IdleTask.Task_Name,"idleTask");
    MYRTOS_IdleTask.Stack_Size=300;
    MYRTOS_IdleTask.Priority=255;
    MYRTOS_IdleTask.P_TaskEntry=MYRTOS_idleTask;

    error+=MYRTOS_CreateTask(&MYRTOS_IdleTask);
	return error;
}

MYRTOS_ErrorID MYRTOS_CreateTask(Task_ref* Tref)
{
	MYRTOS_ErrorID error = NO_ERROR;
	//Create Its OWN PSP stack
	Tref->_S_PSP_Task=Os_Control._PSP_Task_Locator;
	Tref->_E_PSP_Task=(unsigned int *)((unsigned int)Tref->_S_PSP_Task -(unsigned int) Tref->Stack_Size);
	//Check task stack size exceeded the PSP stack
	if(Tref->_E_PSP_Task<&_eheap)
	{
		return Task_exceeded_StackSize;
	}
	Os_Control._PSP_Task_Locator=(unsigned int*)((unsigned int)Tref->_E_PSP_Task - 8);
	//	-				-
	//	- _S_PSP_Task	-
	//	-	Task Stack	-
	//	- _E_PSP_Task	-
	//	-				-
	//	- _eheap		-
	//	-				-
	MyRTOS_Create_TaskStack( Tref);
	//update sch Table
	Os_Control.OsTasks[Os_Control.NoOfActiveTasks]=Tref;
	Os_Control.NoOfActiveTasks++;

	//Task State Update -> Suspend
	Tref->Task_State=Suspend;
	return error;
}
void MyRTOS_Create_TaskStack(Task_ref *Tref) {
	/*Task Frame
	 * ======
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 *r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 */
	Tref->Current_PSP = Tref->_S_PSP_Task;

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0x01000000; //DUMMY_XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = (unsigned int) Tref->P_TaskEntry; //pc

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0xFFFFFFFD; //LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP

	for (unsigned int i = 0; i < 13; i++) {
		Tref->Current_PSP--;
		*(Tref->Current_PSP) = 0;
	}

}

MYRTOS_ErrorID MYRTOS_ActivateTask(Task_ref *Tref) {
	MYRTOS_ErrorID error = NO_ERROR;

	Tref->Task_State = Waiting;
	MYRTOS_Os_SVC_Set(SVC_ActivateTask);

	return error;
}

void MYRTOS_TaskWait(unsigned int NoTICKS,Task_ref* Tref)
{
	// Task Should be blocked
	Tref->Task_State=Suspend;
	Tref->Timing_Waiting.Blocking=enable;
	Tref->Timing_Waiting.Ticks_Count=NoTICKS;
	//to be suspended immediately
	MYRTOS_Os_SVC_Set(SVC_TerminateTask);
}

void MYRTOS_Update_TasksWaitingTime()
{
	for(int i=0;i<Os_Control.NoOfActiveTasks;i++)
	{
		if(Os_Control.OsTasks[i]->Task_State==Suspend)
		{
			if(Os_Control.OsTasks[i]->Timing_Waiting.Blocking==enable)
			{
				Os_Control.OsTasks[i]->Timing_Waiting.Ticks_Count--;
				if(Os_Control.OsTasks[i]->Timing_Waiting.Ticks_Count==0)
				{
					Os_Control.OsTasks[i]->Task_State=Waiting;
					Os_Control.OsTasks[i]->Timing_Waiting.Blocking=disable;
					MYRTOS_Os_SVC_Set(SVC_TaskWaitingTime);
				}
			}
		}
	}
}
MYRTOS_ErrorID MYRTOS_TerminateTask(Task_ref * Tref)
{
	MYRTOS_ErrorID error = NO_ERROR;

	Tref->Task_State=Suspend;
	MYRTOS_Os_SVC_Set(SVC_TerminateTask);

	return error;
}
unsigned char IdleTaskLed;
void MYRTOS_idleTask()
{
	while(1)
	{
		IdleTaskLed^=1;
		__asm("wfe");
	}
}

void MYRTOS_STARTOS()
{
	Os_Control.OsModeID=OsRuinning;
	//Set Default "Current Task =Idle Task"
	Os_Control.CurrentTask = &MYRTOS_IdleTask;
	//Activate IDLE Task
	MYRTOS_ActivateTask(&MYRTOS_IdleTask);
	//start ticker
	Start_Ticker();  //1ms

	OS_SET_PSP(Os_Control.CurrentTask->Current_PSP);
	//Switch Thread Mode SP from MSP to PSP
	OS_SWITCH_SP_TO_PSP;
	OS_SWITCH_TO_UNPRIVILEGE;
	MYRTOS_IdleTask.P_TaskEntry();

}
