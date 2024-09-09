/*
 * schedular.h
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */

#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_
#include "CortxMX_Os_Porting.h"


typedef enum{
	NO_ERROR,
	Ready_Queue_init_error,
	Task_exceeded_StackSize
}MYRTOS_ErrorID;

typedef struct
{
	unsigned int Stack_Size;
	unsigned char Priority;
	void (*P_TaskEntry)(void);  // pointer to task c function
	unsigned char AutoStart; // bollean
	unsigned int *_S_PSP_Task;
	unsigned int *_E_PSP_Task;
	unsigned int *Current_PSP;
	char Task_Name[15];
	enum{
		Suspend,
		Waiting,
		Ready,
		Ruinning
	}Task_State;
	struct{
		enum{
			disable,
			enable
		}Blocking;
		unsigned int Ticks_Count;
	}Timing_Waiting;

}Task_ref;
void OS_SVC_Service(int *StackFramePointer);
MYRTOS_ErrorID MYRTOS_Init();
MYRTOS_ErrorID MYRTOS_CreateTask(Task_ref* Tref);
MYRTOS_ErrorID MYRTOS_ActivateTask(Task_ref *Tref);
void MYRTOS_STARTOS();
#endif /* SCHEDULAR_H_ */
