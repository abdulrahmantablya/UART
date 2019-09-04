/*
 * UART.c
 *
 *  Created on: Sep 4, 2019
 *      Author: abdul
 */
#include "UART.h"


void UART_Init(UART_Cfg_S* UART_config)
{

	uint16 UART_BAUDRATE =0u;

	ClrBit(UCSRC,URSEL);



	if(UART_config->DoubleSpeed == UART_DoubleSpeedDisable)
	{
		ClrBit(UCSRA,U2X);
		UART_BAUDRATE= (((F_CPU / (UART_config->baud_rate * 16UL))) - 1);
	}
	else if (UART_config->DoubleSpeed == UART_DoubleSpeedEn)
	{
		SerBit(UCSRA,U2X);
		UART_BAUDRATE= (((F_CPU / (UART_config->baud_rate * 8UL))) - 1);
	}


	UBRRL = (uint8)(UART_BAUDRATE);
	UBRRH = (uint8)((UART_BAUDRATE) >> 8);


	/* enable writing on UCSRC */
	SetBit(UCSRC,URSEL);


	switch(UART_config->DataSize)
	{
		case Bit5 :

			ClrBit(UCSRC,UCSZ0);
			ClrBit(UCSRC,UCSZ1);
			ClrBit(UCSRB,UCSZ2);
			break;

		case Bit6 :

			SetBit(UCSRC,UCSZ0);
			ClrBit(UCSRC,UCSZ1);
			ClrBit(UCSRB,UCSZ2);
			break;

		case Bit7 :

			ClrBit(UCSRC,UCSZ0);
			SetBit(UCSRC,UCSZ1);
			ClrBit(UCSRB,UCSZ2);
			break;

		case Bit8 :

			SetBit(UCSRC,UCSZ0);
			SetBit(UCSRC,UCSZ1);
			ClrBit(UCSRB,UCSZ2);
			break;

		case Bit9 :

			SetBit(UCSRC,UCSZ0);
			SetBit(UCSRC,UCSZ1);
			SetBit(UCSRB,UCSZ2);
			break;

	}


	switch(UART_config->Parity )
	{
		case UART_ParityDisabled :
			ClrBit(UCSRC,UPM0);
			ClrBit(UCSRC,UPM1);
			break;

		case UART_ParityOdd :
			SetBit(UCSRC,UPM0);
			SetBit(UCSRC,UPM1);
			break;
		case UART_ParityEven :
			ClrBit(UCSRC,UPM0);
			SetBit(UCSRC,UPM1);
			break;
	}



	if(UART_config->StopBits == UART_StopBit1 )
	{
		ClrBit(UCSRC,USBS);
	}
	else if (UART_config->StopBits == UART_StopBit2)
	{
		SetBit(UCSRC,USBS);
	}




	if(UART_config->RxInt == UART_RxIntDisabled)
	{
		ClrBit(UCSRB,RXCIE);
	}
	else if (UART_config->RxInt == UART_RxIntEn)
	{
		SetBit(UCSRB,RXCIE);
	}


	if(UART_config->TxInt == UART_TxIntDisabled)
		{
			ClrBit(UCSRB,TXCIE);
		}
		else if (UART_config->TxInt == UART_TxIntEn)
		{
			SetBit(UCSRB,TXCIE);
		}

	if(UART_config->Udr == UART_UdrDisabled)
	{
		ClrBit(UCSRB,UDRIE);
	}
	else if (UART_config->Udr == UART_UdrEn)
	{
		SetBit(UCSRB,UDRIE);
	}






}

void UART_SendChar(uint16 data)
{
	if(UART_DataSize == Bit9 )
	{
		while(! (GetBit(UCSRA,UDRE)) );

		ClrBit(UCSRB,TXB8);

		if(data & 0x0100)
		{
			SetBit(UCSRB,TXB8);
		}
		UDR=(uint8)data;
	}
	else
	{
		while(! (GetBit(UCSRA,UDRE)) );
		UDR=(uint8)data;

	}
}

void UART_ReceiveChar(uint16* data_ptr)
{
	uint8 status;
	uint8 data_low;
	uint8 data_high;


	data_high=UCSRB;

	data_low=UDR;


	if(UART_DataSize == Bit9)
	{
		while(! (GetBit(UCSRA,RXC)) );

		if(GetBit(UCSRA,FE) || (GetBit(UCSRA,DOR)) || (GetBit(UCSRA,PE)) )
		{

		}
		else
		{
			data_high = (data_high >> 1) & 0x01;

			*data_ptr = (uint16)((data_high << 8) | data_low);
		}

	}
	else
	{
		while(! (GetBit(UCSRA,RXC)) );

			*((uint8)data_ptr)=UDR;
	}


}

void Start_Comm(void)
{
	SetBit(UCSRB,TXEN);
	SetBit(UCSRB,RXEN);

}

void Stop_Comm(void)
{
	ClrBit(UCSRB,TXEN);
	ClrBit(UCSRB,RXEN);
}

