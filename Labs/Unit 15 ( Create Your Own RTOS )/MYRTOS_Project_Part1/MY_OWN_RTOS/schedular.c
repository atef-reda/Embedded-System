/*
 * schedular.c
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */




#include "MYRTOS_FIFO.h"
#include "string.h"
void MYRTOS_idleTask();
void MyRTOS_Create_TaskStack(Task_ref* Tref);

struct {
	Task_ref OsTasks[20];
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


FIFO_Buf_t Ready_QUEUE ;
Task_ref *Ready_QUEUE_FIFO[100];
Task_ref MYRTOS_IdleTask;
  void OS_SVC_Service(int *StackFramePointer)
  {
  	//os_svc_set stack -> r0 -> argument0 = StackFramePointer
  	//os_svc_set stack r0,r1,r2,r3,r12,lr,pc,xpsp
  	unsigned char svc_number;

  	svc_number=((unsigned char *)StackFramePointer[6])[-2];

  	switch(svc_number)
  	{
  	case 1: //Activate Task
  		break;
      case 2: //Terminate Task

  		break;
  	case 3: //

  		break;
  	case 4: //

  		break;

  	}

  }

void OS_SVC_Set(int SVC_ID)
{

	switch (SVC_ID)
	{
	case 1: //Activate Task
		__asm("svc #0x01");
		break;
	case 2: //
		__asm("svc #0x02");
		break;
	case 3: //
		__asm("svc #0x03");
		break;
	case 4: //
		__asm("svc #0x04");
		break;
	}

}

void PendSV_Handler()
{

}











void MYRTOS_Create_MainStack(void)
{
	Os_Control._S_MSP_Task=&_estack;
	Os_Control._E_MSP_Task=(unsigned int)Os_Control._S_MSP_Task-(unsigned int)Main_Stack_Size;
	//aligned 8 byte
	Os_Control._PSP_Task_Locator=(unsigned int)Os_Control._E_MSP_Task-8;

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
	Tref->_E_PSP_Task=(unsigned int)Tref->_S_PSP_Task -(unsigned int) Tref->Stack_Size;
	//Check task stack size exceeded the PSP stack
	if(Tref->_E_PSP_Task<(unsigned int)&_eheap)
	{
		return Task_exceeded_StackSize;
	}
	Os_Control._PSP_Task_Locator=((unsigned int)Tref->_E_PSP_Task - 8);
	//	-				-
	//	- _S_PSP_Task	-
	//	-	Task Stack	-
	//	- _E_PSP_Task	-
	//	-				-
	//	- _eheap		-
	//	-				-
	MyRTOS_Create_TaskStack( Tref);
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
void MYRTOS_idleTask()
{
	while(1)
	{
		__asm("NOP");
	}
}
