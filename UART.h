/*
 * UART.h
 *
 *  Created on: Jan 9, 2016
 *      Author: Ercle
 */

#ifndef UART_H_
#define UART_H_

#include <MSP430.h>
#include <stdint.h>

#define FCLK		16000000L

void UART_Init();

int16_t UART_Receive();

void UART_Send(uint8_t data);
void UART_SendStr(char *str);



#endif /* UART_H_ */
