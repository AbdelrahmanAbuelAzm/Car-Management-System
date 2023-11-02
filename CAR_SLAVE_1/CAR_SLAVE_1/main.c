/*
 * CAR_SLAVE_1.c
 *
 * Created: 11/1/2023 7:22:05 AM
 * Author : DELL
 */ 

//#include <avr/io.h>
#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "UTILIS.h"
#include "DIO_Interface.h"
#include "DIO_Config.h"
#include "SPI.h"
#include "Servo_Motor.h"
#include "TIMER_INTERFAC.h"
#include "TIMER_SERVICE.h"
#include "MOTOR_Interface.h"
#include "ADC_INTERFACE.h"

int main(void)
{
	
	// main peripherals init
	DIO_Init();
	SPI_Init();
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	ADC_Channel_Selection(CH_0);
	
	// timer1 init
	OCR1A=19999;
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	OCR1B=999;
	
	//global interrupt enable
	 GLOBAL_ENABLE();
	 
	//Local Variables
	u8 spi_reading=0;
	u8 D1_Previous_Angle=Door_Close;
	u8 D2_Previous_Angle=Door_Close;
	u8 temp=0;
	
	
    
    while (1) 
    {
		
		temp=Temp_Read();
		spi_reading=SPI_SendReceive(temp); // temp sensor
		if(spi_reading!=0)
		{
			DIO_TogglePin(PINA1);
			//delay(10);
			//spi_reading=0;
		}
		if(spi_reading=='z') // door1
		{
		    D1_Previous_Angle= Car_Door_Command(Door_1, D1_Previous_Angle,PINC0);
			spi_reading=0;
		}
		else if(spi_reading=='x')//door2
		{
			D2_Previous_Angle= Car_Door_Command(Door_2, D2_Previous_Angle,PINC1);
			spi_reading=0;
		}
		else if(spi_reading=='c')// temp sensor
		{
			spi_reading=0;
			spi_reading=SPI_SendReceive(temp);
			spi_reading=0;
		}
		
		
		
    }
}

