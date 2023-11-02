/*
 * CAR_MASTER.c
 *
 * Created: 11/1/2023 7:21:05 AM
 * Author : DELL
 */ 

//#include <avr/io.h>
#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "UTILIS.h"
#include "DIO_Interface.h"
#include "DIO_Config.h"
#include "UART_INTERFACE.h"
#include "UART_Services.h"
#include "SPI.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"


volatile u8 Uart_RX_flag=0;

void Reciv_func(void)
{
	
	Uart_RX_flag=1;
}

/*
uart commands
1-DC_Motor

  q for full speed 
  w for stop
  r for turn right
  l for turn left 
  1-9 for dc motor speed

2- servo motor
 z for door1
 x for door2
 a for door3
 s for door4

4- temp 
  c for load the new reading of temp


*/

int main(void)
{
	// main peripherals init
	DIO_Init();
	LCD_Init();
	UART_Init();
	SPI_Init();
	
	// functions init
	UART_RX_InterruptEnable();
	GLOBAL_ENABLE();
	UART_RX_SetCallBack(Reciv_func);
	
	
	u8 uart_reading=0,spi_reading=0;
	
	LCD_GoTo(0,0);
	LCD_WriteString("Pressed Char:");
	
	LCD_GoTo(1,0);
	LCD_WriteString("Car Door:");
	
	LCD_GoTo(2,0);
	LCD_WriteString("CAR Motor:");
	LCD_GoTo(2,11);
	LCD_WriteString("0%");
	
	LCD_GoTo(3,0);
	LCD_WriteString("Engine Temp:");
	
     while (1) 
    {
		
		
		if(Uart_RX_flag==1)
		{
			uart_reading=UART_ReceiveNoBlock();
			
			if(uart_reading=='z' || uart_reading=='x' || uart_reading=='c')
			{
				DIO_WritePin(PINC0,LOW);
				//DIO_WritePin(PINC1,HIGH);
				spi_reading=SPI_SendReceive(uart_reading);
				LCD_GoTo(0,15);
				LCD_WriteChar(uart_reading);
				LCD_GoTo(3,14);
				LCD_WriteNumber(spi_reading);
				DIO_TogglePin(PINA1);
				LCD_Diplay_Car_Management(uart_reading);
				Uart_RX_flag=0;
				delay(50);
				//DIO_WritePin(PINC0,HIGH);
			}
			else if(uart_reading=='a' || uart_reading=='s' || uart_reading=='q' || uart_reading=='w' || uart_reading=='r' || uart_reading=='l' || ( uart_reading>='1' && uart_reading<='9') )
			{
				DIO_WritePin(PINC1,LOW);
				//DIO_WritePin(PINC0,HIGH);
				spi_reading=SPI_SendReceive(uart_reading);
				LCD_GoTo(0,15);
				LCD_WriteChar(uart_reading);
				//LCD_GoTo(3,0);
				//LCD_WriteNumber(spi_reading);
				DIO_TogglePin(PINA1);
				LCD_Diplay_Car_Management(uart_reading);
				Uart_RX_flag=0;
				delay(50);
				//DIO_WritePin(PINC0,HIGH);
			}
			spi_reading=0;
			
			
			
		}
// 		if(spi_reading!=0)
// 		{
// 			
// 			
// 		}
		
    }
}

