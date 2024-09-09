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



  __attribute ((naked)) void SVC_Handler()
  {
	  // lr and 0100 to check about 2nd bit
  	__asm("tst lr,#4 \n\t"
  			"ITE EQ \n\t"
  			"mrseq r0,MSP \n\t"
  			"mrsne r0,PSP \n\t"
  			"B OS_SVC_Service");
  }


  void HW_Init()
  {
	  //initalize clock tree (RCC->Systic Timer & CPU) 8 MHz
	  //init HW
	  //clock tree
	  //rcc default makes cpu clocks & systic timer = 8 Mz
	  // 1 clock ==> .125us
	  // x count ==> 1ms
	  // x = 8000 count
  }



