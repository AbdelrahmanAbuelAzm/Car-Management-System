#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "Motor_cfg.h"
#include "MOTOR_Interface.h"


void MOTOR_Init(void)
{
	MOTOR_TYPE i;
	for(i=M1;i<TOTAL_MOTOR;i++)
	{
		MOTOR_Stop(i);
	}
}

void MOTOR_Speed(MOTOR_TYPE m,u8 speed)
{
	if(speed>MOTOR_MAX_SPEED)
	{
		
			speed=MOTOR_MAX_SPEED;
			
		
	}
}
void MOTOR_Stop(MOTOR_TYPE m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_In1,LOW);
		DIO_WritePin(M1_In2,LOW);
		break;
		case M2:
		DIO_WritePin(M2_In1,LOW);
		DIO_WritePin(M2_In2,LOW);
		break;
		case M3:
		DIO_WritePin(M3_In1,LOW);
		DIO_WritePin(M3_In2,LOW);
		break;
		case M4:
		DIO_WritePin(M4_In1,LOW);
		DIO_WritePin(M4_In2,LOW);
		break;
		default:
		break;
		
	}
	
}

void MOTOR_CW(MOTOR_TYPE m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_In1,LOW);
		DIO_WritePin(M1_In2,HIGH);
		break;
		case M2:
		DIO_WritePin(M2_In1,LOW);
		DIO_WritePin(M2_In2,HIGH);
		break;
		case M3:
		DIO_WritePin(M3_In1,LOW);
		DIO_WritePin(M3_In2,HIGH);
		break;
		case M4:
		DIO_WritePin(M4_In1,LOW);
		DIO_WritePin(M4_In2,HIGH);
		break;
		default:
		break;
	}
}

void Case_M1(void)
{
	DIO_WritePin(M1_In1,LOW);
	DIO_WritePin(M1_In2,HIGH);
}
void Case_M2(void)
{
	DIO_WritePin(M2_In1,LOW);
	DIO_WritePin(M2_In2,HIGH);
}
void Case_M3(void)
{
	DIO_WritePin(M3_In1,LOW);
	DIO_WritePin(M3_In2,HIGH);
}
void Case_M4(void)
{
	DIO_WritePin(M4_In1,LOW);
	DIO_WritePin(M4_In2,HIGH);
}
void(*MOTOR_Cases[TOTAL_MOTOR])(void)={Case_M1,Case_M2,Case_M3,Case_M4};// function taking array of pointer to function
	
void MOTOR_CW2(MOTOR_TYPE m)
{
	
		MOTOR_Cases[m]();
		
		
}
void MOTOR_CCW(MOTOR_TYPE m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_In1,HIGH);
		DIO_WritePin(M1_In2,LOW);
		break;
		case M2:
		DIO_WritePin(M2_In1,HIGH);
		DIO_WritePin(M2_In2,LOW);
		break;
		case M3:
		DIO_WritePin(M3_In1,HIGH);
		DIO_WritePin(M3_In2,LOW);
		break;
		case M4:
		DIO_WritePin(M4_In1,HIGH);
		DIO_WritePin(M4_In2,LOW);
		break;
		default:
		break;
	}
}