
#include "STD_TYPES.h"
#include "Servo_Motor.h"
#include "TIMER_INTERFAC.h"
#include "TIMER_SERVICE.h"
#include "DIO_Interface.h"




void Servo_SetAngle(u8 angle)
{
	if(angle>180)
	{
		angle=180;
	}
	OCR1B=((angle*(u32)1000)/(u32)180)+999;
}

CAR_DOOR_STATUS_t Car_Door_Command(CAR_DOOR_NO_t door_num,CAR_DOOR_STATUS_t Previous_Servo_Angle,u8 OUT_PIN)
{
	
	if(Previous_Servo_Angle==Door_Close)
	{
		DIO_WritePin(OUT_PIN,HIGH);
		//delay(10);  // set pin of and gate for d1
		Servo_SetAngle(Door_Open);
		Previous_Servo_Angle=Door_Open;
		delay(50);
		DIO_WritePin(OUT_PIN,LOW);
		
	}
	else if(Previous_Servo_Angle==Door_Open)
	{
		DIO_WritePin(OUT_PIN,HIGH);  // set pin of and gate for d1
		//delay(10);
		Servo_SetAngle(Door_Close);
		Previous_Servo_Angle=Door_Close;
		delay(50);
		DIO_WritePin(OUT_PIN,LOW);
		
	}
	return Previous_Servo_Angle;
}