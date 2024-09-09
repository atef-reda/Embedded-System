/*
 * MYRTOS_FIFO.c
 *
 *  Created on: Aug 18, 2024
 *      Author: redaa
 */

#include "MYRTOS_FIFO.h"


Buffer_Status FIFO_init(FIFO_Buf_t *fifo, Element_Type *buff,
		unsigned int length) {
	if (!buff)
		return FIFO_NULL;

	fifo->base = buff;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->length = length;
	fifo->counter = 0;

	return FIFO_NO_ERROR;
}
Buffer_Status FIFO_enqueue (FIFO_Buf_t* fifo,Element_Type item)
{
	// fifo null
	if(!fifo->base || !fifo->length)
		return FIFO_NULL;


	//fifo full
	if(fifo->head == fifo->tail && fifo->counter == fifo->length)
		return FIFO_FULL;

	*(fifo->tail)=item;
	fifo->counter++;


	//for circular enqueue or normal enqueue
	if(fifo->tail == ( (unsigned int)fifo->base +(4*fifo->length) )-4)
		fifo->tail=fifo->base;
	else
		fifo->tail++;

	return FIFO_NO_ERROR;
}


Buffer_Status FIFO_dequeue (FIFO_Buf_t* fifo,Element_Type* item)
{
	/* check fifo valid */
	if (!fifo->base || !fifo->length)
		return FIFO_NULL;

	/* fifo empty */
	if (fifo->head == fifo->tail)
		return FIFO_EMPTY;



	*item = *(fifo->head);
	fifo->counter--;

	/* circular dequeue */
	if (fifo->head == (((unsigned int)fifo->base + (4*fifo->length )) - 4 ))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_NO_ERROR;
}

Buffer_Status FIFO_is_full (FIFO_Buf_t* fifo){

	if(!fifo->head || !fifo->base || !fifo->tail)
		return FIFO_NULL;
	if(fifo->counter == fifo->length)
		return FIFO_FULL;

	return FIFO_NO_ERROR;
}
void FIFO_print (FIFO_Buf_t* fifo);
