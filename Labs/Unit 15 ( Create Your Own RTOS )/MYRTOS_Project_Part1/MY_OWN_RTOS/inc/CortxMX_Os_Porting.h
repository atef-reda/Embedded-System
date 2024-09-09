/*
 * CortxMX_Os_Porting.h
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */

#ifndef CORTXMX_OS_PORTING_H_
#define CORTXMX_OS_PORTING_H_

#include "ARMCM3.h"


extern int _estack;
extern int _eheap;
#define Main_Stack_Size       3072

#define OS_SET_PSP(add)               __asm volatile("mov r0,%0 \n\t msr PSP,r0"::"r"(add))
#define OS_GET_PSP(add)               __asm volatile("mrs r0,PSP \n\t mov %0,r0":"=r"(add))

#define OS_SWITCH_SP_TO_PSP           __asm volatile("MRS r0,CONTROL \n\t ORR r0,r0,#0x02 \n\t msr CONTROL ,r0")
#define OS_SWITCH_SP_TO_MSP           __asm volatile("MRS r0,CONTROL \n\t AND r0,r0,#0x05 \n\t msr CONTROL ,r0")
// clear bit0 in CONTROL Register
#define OS_SWITCH_TO_PRIVILEGE        __asm volatile("MRS r0,CONTROL \n\t AND r0,r0,#0x06 \n\t msr CONTROL ,r0")
// set bit0 in CONTROL Register
#define OS_SWITCH_TO_UNPRIVILEGE      __asm volatile("MRS r0,CONTROL \n\t ORR r0,#0x01 \n\t msr CONTROL ,r0")

#define OS_GENERATE_EXEPTION          __asm volatile("SVC #0x3")

void HW_Init();

#endif /* CORTXMX_OS_PORTING_H_ */
