/*
 * UART.h
 *
 *  Created on: Sep 4, 2019
 *      Author: abdul
 */

#ifndef UART_H_
#define UART_H_

#include "DIO.h"



#ifndef F_CPU

#define F_CPU 8000000UL //8MHz Clock frequency

#endif

/*******************************************************************************
 *                          Mapped Registers                                   *
 *******************************************************************************/
#define UDR   (*(volatile uint8 *)0x002C)	/* USART I/O Data Register – UDR */
#define UCSRA (*(volatile uint8 *)0x2B)	/* USART Control and Status Register A – UCSRA */
#define UCSRB (*(volatile uint8 *)0x2A)	/* USART Control and Status Register B – UCSRB */
#define UCSRC (*(volatile uint8 *)0x40)	/* USART Control and Status Register C – UCSRC */
#define UBRRH (*(volatile uint8 *)0x40)	/* USART Baud Rate Registers – UBRRH */
#define UBRRL (*(volatile uint8 *)0x29)	/* USART Baud Rate Registers – UBRRL */

/*******************************************************************************
 *                          Registers Pins                                     *
 *******************************************************************************/

/**************************** UCSRA PINS ***************************************/
#define RXC  (7u)		/*Bit 7 – RXC: USART Receive Complete*/
#define TXC  (6u)		/*Bit 6 – TXC: USART Transmit Complete*/
#define UDRE (5u)		/*Bit 5 – UDRE: USART Data Register Empty*/
#define FE   (4u)		/*Bit 4 – FE: Frame Error*/
#define DOR  (3u)		/*Bit 3 – DOR: Data OverRun*/
#define PE   (2u)		/*Bit 2 – PE: Parity Error*/
#define U2X	 (1u)		/*Bit 1 – U2X: Double the USART Transmission Speed*/
#define MPCM (0u)		/*Bit 0 – MPCM: Multi-processor Communication Mode*/

/**************************** UCSRB PINS ***************************************/
#define RXCIE  (7u)		/*Bit 7 – RXCIE: RX Complete Interrupt Enable*/
#define TXCIE  (6u)		/*Bit 6 – TXCIE: TX Complete Interrupt Enable*/
#define UDRIE  (5u)		/*Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable*/
#define RXEN   (4u)		/*Bit 4 – RXEN: Receiver Enable*/
#define TXEN   (3u)		/*Bit 3 – TXEN: Transmitter Enable*/
#define UCSZ2  (2u)		/*Bit 2 – UCSZ2: Character Size*/
#define RXB8   (1u)		/*Bit 1 – RXB8: Receive Data Bit 8*/
#define TXB8   (0u)		/*Bit 0 – TXB8: Transmit Data Bit 8*/

/**************************** UCSRC PINS ***************************************/
#define URSEL  (7u)		/*Bit 7 – URSEL: Register Select*/
#define UMSEL  (6u)		/*Bit 6 – UMSEL: USART Mode Select*/
#define UPM1   (5u)		/*Bit 5 – UPM1: Parity Mode*/
#define UPM0   (4u)		/*Bit 4 – UPM0: Parity Mode*/
#define USBS   (3u)		/*Bit 3 – USBS: Stop Bit Select*/
#define UCSZ1  (2u)		/*Bit 2 – UCSZ1: Character Size*/
#define UCSZ0  (1u)		/*Bit 1 – UCSZ0: Character Size*/
#define UCPOL  (0u)		/*Bit 0 – UCPOL: Clock Polarity*/


/* Double Speed Mode Enable/Disable */
typedef enum {
	UART_DoubleSpeedDisable = 0u,
	UART_DoubleSpeedEn      = 1u
}UART_DoubleSpeed;

/* Transmit Interrupt Enable/Disable */
typedef enum {
	UART_TxIntDisabled = 0u,
	UART_TxIntEn       = 1u
}UART_TxInt;

/* Receive Interrupt Enable/Disable */
typedef enum {
	UART_RxIntDisabled = 0u,
	UART_RxIntEn       = 1u
}UART_RxInt;

/* UDR Interrupt Enable/Disable */
typedef enum {
	UART_UdrDisabled = 0u,
	UART_UdrEn       = 1u
}UART_UdrInt;

/* Data Frame bits numbers*/
typedef enum {
	Bit5 = 5u,
	Bit6 = 6u,
	Bit7 = 7u,
	Bit8 = 8u,
	Bit9 = 9u
}UART_DataSize;

/*Parity Bits configurations */
typedef enum {
	UART_ParityDisabled = 0u,
	UART_ParityOdd      = 1u,
	UART_ParityEven     = 2u
}UART_Parity;

/* check number of stop bits*/
typedef enum {
	UART_StopBit1 = 1u,
	UART_StopBit2 = 2u
}UART_StopBits;

/*check the function execution*/
typedef enum {
	NotOk = 0u,
	Ok    = 1u
}Status;

typedef struct
{
	uint16 				baud_rate;
	UART_DoubleSpeed	DoubleSpeed;
	UART_TxInt			TxInt;
	UART_RxInt			RxInt;
	UART_UdrInt			Udr;
	UART_DataSize		DataSize;
	UART_Parity			Parity;
	UART_StopBits		StopBits;

}UART_Cfg_S;

void UART_Init(UART_Cfg_S* UART_config);

void UART_ReceiveChar(uint16* data_ptr);

void UART_SendChar(uint16 data);

void Start_Comm(void);

void Stop_Comm(void);

void UART_Send(uint16* data_ptr);

void UART_Receive(uint16* data_ptr);

#endif /* UART_H_ */
