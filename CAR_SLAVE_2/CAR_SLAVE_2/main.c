/*
 * CAR_SLAVE_2.c
 *
 * Created: 11/1/2023 7:22:57 AM
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

DIO_Init();
SPI_Init();
Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
ADC_Init(VREF_AVCC,ADC_SCALER_64);
ADC_Channel_Selection(CH_0);
PWM_TIMER0_Init();

// timer1 init
OCR1A=19999;
Timer1_OCRB1Mode(OCRB_NON_INVERTING);
OCR1B=999;

//global interrupt enable
GLOBAL_ENABLE();

//Local Variables
u8 spi_reading=0;
u8 D3_Previous_Angle=Door_Close;
u8 D4_Previous_Angle=Door_Close;




while (1)
{
	
	
	spi_reading=SPI_SendReceive(0); // temp sensor
	if(spi_reading!=0)
	{
		DIO_TogglePin(PINA1);
		//delay(10);
		//spi_reading=0;
	}
	if(spi_reading=='a') // door3
	{
		D3_Previous_Angle= Car_Door_Command(Door_1, D3_Previous_Angle,PINC0);
		spi_reading=0;
	}
	else if(spi_reading=='s')//door4
	{
		D4_Previous_Angle= Car_Door_Command(Door_2, D4_Previous_Angle,PINC1);
		spi_reading=0;
	}
	else if(spi_reading=='q')// DC M 100% 
	{
		DIO_WritePin(PINC3,HIGH);
		DIO_WritePin(PINC4,HIGH);
		DIO_WritePin(PINC5,HIGH);
		PWM_timer0_Duty(100);
		spi_reading=0;
	}
	else if(spi_reading=='w')   //DC M 0% 
	{
		DIO_WritePin(PINC3,LOW);
		DIO_WritePin(PINC4,LOW);
		DIO_WritePin(PINC5,LOW);
		PWM_timer0_Duty(0);
		spi_reading=0;
	}
	else if(spi_reading=='r')   //DC M turn right 
	{
		DIO_WritePin(PINC3,LOW);
		DIO_WritePin(PINC4,HIGH);
		DIO_WritePin(PINC5,HIGH);
		PWM_timer0_Duty(100);
		spi_reading=0;
	}
	else if(spi_reading=='l')   //DC M turn left
	{
		DIO_WritePin(PINC3,HIGH);
		DIO_WritePin(PINC4,LOW);
		DIO_WritePin(PINC5,HIGH);
		PWM_timer0_Duty(100);
		spi_reading=0;
	}
	else if(spi_reading>='1' && spi_reading<='9' )// DC M Ratio
	{
		DIO_WritePin(PINC3,HIGH);
		DIO_WritePin(PINC4,HIGH);
		DIO_WritePin(PINC5,HIGH);
		if(spi_reading=='1')
		{
			PWM_timer0_Duty(10);
		}
		else if (spi_reading=='2')
		{
			PWM_timer0_Duty(20);
		}
		else if (spi_reading=='3')
		{
			PWM_timer0_Duty(30);
		}
		else if (spi_reading=='4')
		{
			PWM_timer0_Duty(40);
		}
		else if (spi_reading=='5')
		{
			PWM_timer0_Duty(50);
		}
		else if (spi_reading=='6')
		{
			PWM_timer0_Duty(60);
		}
		else if (spi_reading=='7')
		{
			PWM_timer0_Duty(70);
		}
		else if (spi_reading=='8')
		{
			PWM_timer0_Duty(80);
		}
		else if (spi_reading=='9')
		{
			PWM_timer0_Duty(90);
		}
		
		spi_reading=0;
	}
	
	
	
	
	
}
}

