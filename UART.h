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
#include "Util.h"

#define BAUD		9600

#define RX_BUFFER_SIZE	8	//Must be power of 2
#define RX_BUFFER_MASK	(RX_BUFFER_SIZE - 1)

extern uint8_t _rxStart;
extern uint8_t _rxEnd;
extern uint8_t _rxBuffer[RX_BUFFER_SIZE];

void UART_Init();

void UART_Send(uint8_t data);
void UART_SendStr(char *str);

int16_t UART_Read();
uint8_t UART_ReadAvailable();

#endif /* UART_H_ */
