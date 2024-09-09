#include "uart.h"

unsigned char name[100]="eng:- atef reda mohammed";
unsigned char const name1[100]="eng:- atef reda mohammed";

void main(void)
{
	uart_send_string(name);
}