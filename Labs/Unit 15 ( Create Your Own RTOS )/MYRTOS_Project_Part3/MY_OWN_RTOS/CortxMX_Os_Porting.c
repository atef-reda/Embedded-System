/*
 * CortxMX_Os_Porting.c
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */



#include "CortxMX_Os_Porting.h"


  void HardFault_Handler (void)
  {
	  while(1);
  }
  void	MemManage_Handler (void)
  {
	  while(1);
  }
  void	BusFault_Handler (void)
  {
	  while(1);
  }
  void	UsageFault_Handler (void)
  {
	  while(1);
  }


  // we use this __attribute ((naked)):
  //to deal with this function as asm code and not make stack for it
  __attribute ((naked)) void SVC_Handler()
  {
	  // lr and 0100 to check about 2nd bit
  	__asm("tst lr,#4 \n\t"
  			"ITE EQ \n\t"
  			"mrseq r0,MSP \n\t"
  			"mrsne r0,PSP \n\t"
  			"B OS_SVC_Service");
  }


  void HW_Init() {
	//initalize clock tree (RCC->Systic Timer & CPU) 8 MHz
	//init HW
	//clock tree
	//rcc default makes cpu clocks & systic timer = 8 Mz
	// 1 clock ==> .125us
	// x count ==> 1ms
	// x = 8000 count
	//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	//SysTICK have a priority 15
	__NVIC_SetPriority(PendSV_IRQn, 15);
}

void trigger_OS_PendSV()

{
	//pendsv set pending
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void Start_Ticker() {
	//rcc default makes cpu clocks & systic timer = 8 Mz
	// 1 clock ==> .125us
	// x count ==> 1ms
	// x = 8000 count
	SysTick_Config(8000);
}

unsigned char Systic_Led;
void SysTick_Handler() {
	Systic_Led^=1;
	//Determine Pcurrent & Pnext
	Decide_WhatNext();
	//Switch Context & restore
	trigger_OS_PendSV();
}

