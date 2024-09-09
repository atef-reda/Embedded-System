/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "STM32F103x6.h"
#include "stm32f103x6_GPIO_Driver.h"
#include "stm32f103x6_EXTI_Driver.h"

#include "../CMSIS_V5/core_cm3.h"

#define TASKA_STACK_SIZE           100 //BYTE
#define TASKB_STACK_SIZE           100 //BYTE

extern int _estack;

// Main Stack
unsigned int S_MSP=&_estack;
unsigned int E_MSP;

//process stack task A
unsigned int S_PSP_TA;
unsigned int E_PSP_TA;

//process stack task B
unsigned int S_PSP_TB;
unsigned int E_PSP_TB;

#define OS_SET_PSP(add)               __asm volatile("mov r0,%0 \n\t msr PSP,r0"::"r"(add))
#define OS_SWITCH_SP_TO_PSP           __asm volatile("MRS r0,CONTROL \n\t ORR r0,r0,#0x02 \n\t msr CONTROL ,r0")
#define OS_SWITCH_SP_TO_MSP           __asm volatile("MRS r0,CONTROL \n\t AND r0,r0,#0x05 \n\t msr CONTROL ,r0")
#define OS_SWITCH_TO_PRIVILEGE        __asm volatile("MRS r0,CONTROL \n\t AND r0,r0,#0x06 \n\t msr CONTROL ,r0")
#define OS_SWITCH_TO_UNPRIVILEGE      __asm volatile("MRS r0,CONTROL \n\t ORR r0,#0x01 \n\t msr CONTROL ,r0")

#define OS_GENERATE_EXEPTION          __asm volatile("SVC #0x3")
typedef enum
{
	privileged,
	unprivileged
}Privilege_Level;
void CPU_Switch_Access_Level(Privilege_Level level);
unsigned int TaskA_Flag,TaskB_Flag,flag = 0 ;
void delay(int delay)
{
	uint32_t i,j;

	for (i = 0; i < delay; i++)
	{
		for(j = 0; j < 255 ; j++);
	}
}

int TaskA(int a,int b,int c)
{
	return a+b+c;
}
int TaskB(int a,int b,int c,int d)
{
	return a+b+c+d;
}
void MainOs()
{
	//Main Stack
	E_MSP=S_MSP-512;

	//Process Stack TaskA
	S_PSP_TA=E_MSP-8;
	E_PSP_TA=S_PSP_TA-TASKA_STACK_SIZE;

	//Process Stack TaskB
	S_PSP_TB=E_PSP_TA-8;
	E_PSP_TB=S_PSP_TB-TASKB_STACK_SIZE;
}
void EXTI9_CallBack()
{
	if(flag==0)
	{
		TaskA_Flag=1;
		flag=1;
	}else if(flag==1)
	{
		TaskB_Flag=1;
		flag=0;
	}
}


void CPU_Switch_Access_Level(Privilege_Level level)
{
	switch (level)
	{
	case privileged:
		//clear bit0 in CONTROL
		__asm("mrs r3,CONTROL");
		__asm("LSR r3,r3,1");
		__asm("LSl r3,r3,1");
		__asm("msr CONTROL,r3");
		break;
	case unprivileged:
		//set bit0 in CONTROL
		__asm("mrs r3,CONTROL");
		__asm("ORR r3,0x01");
		__asm("msr CONTROL,r3");
		break;
	}
}

void OS_SVC_Service(int *StackFramePointer)
{
	//os_svc_set stack -> r0 -> argument0 = StackFramePointer
	//os_svc_set stack r0,r1,r2,r3,r12,lr,pc,xpsp
	unsigned char svc_number;
	int val1,val2;
	svc_number=((unsigned char *)StackFramePointer[6])[-2];
	val1=StackFramePointer[0];
	val2=StackFramePointer[1];

	switch(svc_number)
	{
	case 1: //add
		StackFramePointer[0]=val1+val2;
		break;
    case 2: //sub
    	StackFramePointer[0]=val1-val2;
		break;
	case 3: //mul
		StackFramePointer[0]=val1*val2;
		break;

	}

}
__attribute ((naked)) void SVC_Handler()
{
	__asm("tst lr,#4 \n\t" // lr and 0100 to check about 2nd bit
			"ITE EQ \n\t"
			"mrseq r0,MSP \n\t"
			"mrsne r0,PSP \n\t"
			"B OS_SVC_Service");
}


int OS_SVC_Set(int a,int b,int SVC_ID)
{
	int result;
	switch (SVC_ID)
	{
	case 1: //add
		__asm("svc #0x01");
		break;
	case 2: //sub
		__asm("svc #0x02");
		break;
	case 3: //mul
		__asm("svc #0x03");
		break;
	}
	__asm("mov %0,r0 ":"=r"(result):);
	return result;
}

int main(void)
{
//	RCC_GPIOA_CLK_EN() ;
//	RCC_GPIOB_CLK_EN() ;
//	RCC_AFIO_CLK_EN() ;
//
//
//	EXTI_PinConfig_t EXTI_RQ ;
//
//	EXTI_RQ.EXTI_PIN =EXTI_Pin9 ;
//	EXTI_RQ.GPIO_Port =GPIOB ;
//	EXTI_RQ.trigger_case =EXTI_Trigger_Rising ;
//	EXTI_RQ.P_IRQ_CallBack =EXTI9_CallBack ;
//	EXTI_RQ.IRQ_Enable =EXTI_IRQ_Enable ;
//
//	MCAL_EXTI_GPIO_Init(&EXTI_RQ) ;
//
//	MainOs();
	flag=1;
	flag=OS_SVC_Set(3,3,1); //add
	flag=OS_SVC_Set(3,3,2); //sub
	flag=OS_SVC_Set(3,3,3); //mul
	__asm("nop \n\t nop \n\t nop \n\t");

	// note in this step can't modify on special register
	CPU_Switch_Access_Level(unprivileged);
	CPU_Switch_Access_Level(privileged);

	__asm("nop \n\t nop \n\t nop \n\t");
	while(1)
	{
      if(TaskA_Flag==1)
      {
    	  // set psp register =S_PSP_TA
    	  OS_SET_PSP(S_PSP_TA);
    	  // sp ==> psp
    	  OS_SWITCH_SP_TO_PSP;
    	  //switch privilege ==> unprivilege
    	  OS_SWITCH_TO_UNPRIVILEGE;
    	  TaskA_Flag=TaskA(1, 2, 3);
    	  //switch unprivilege ==> privilege
    	  OS_GENERATE_EXEPTION;
    	  //ps ==> msp
    	  OS_SWITCH_SP_TO_MSP;
      }else if(TaskB_Flag==1)
      {
    	  // set psp register =S_PSP_TB
    	  OS_SET_PSP(S_PSP_TB);
    	  // sp ==> psp
    	  OS_SWITCH_SP_TO_PSP;
    	  //switch privilege ==> unprivilege
    	  OS_SWITCH_TO_UNPRIVILEGE;
    	  TaskB_Flag=TaskB(1, 2, 3,4);
    	  //switch unprivilege ==> privilege
    	  OS_GENERATE_EXEPTION;
    	  //ps ==> msp
    	  OS_SWITCH_SP_TO_MSP;
    	  //ps ==> msp

      }
	}
}


void NMI_Handler()
{

}
void  HardFault_Handler()
{
	__asm("mrs r3,CONTROL");
	__asm("LSR r3,r3,1");
	__asm("LSl r3,r3,1");
	__asm("msr CONTROL,r3");
}
void 	MemManage_Handler()
{

}
void 	BusFault_Handler()
{

}
void 	UsageFault_Handler()
{

}
