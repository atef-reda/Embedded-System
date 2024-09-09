/*
 * MYRTOS_FIFO.h
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */

#ifndef INC_MYRTOS_FIFO_H_
#define INC_MYRTOS_FIFO_H_

#include "stdio.h"
#include"stdint.h"
#include "schedular.h"


#define Element_Type Task_ref*
typedef struct{
	unsigned int counter;
	Element_Type *head;
	Element_Type *tail;
	Element_Type *base;
	unsigned int length;
}FIFO_Buf_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL
}Buffer_Status;

Buffer_Status FIFO_init (FIFO_Buf_t* fifo,Element_Type* buff , unsigned int length);
Buffer_Status FIFO_enqueue (FIFO_Buf_t* fifo,Element_Type item);
Buffer_Status FIFO_dequeue (FIFO_Buf_t* fifo,Element_Type* item);
Buffer_Status FIFO_is_full (FIFO_Buf_t* fifo);
void FIFO_print (FIFO_Buf_t* fifo);



#endif /* INC_MYRTOS_FIFO_H_ */
