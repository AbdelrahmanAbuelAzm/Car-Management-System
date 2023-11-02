/*
 * MOTOR_Interface.h
 *
 * Created: 6/12/2023 12:42:13 AM
 *  Author: DELL
 */ 


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_
typedef enum{
	M1=0,
	M2,
	M3,
	M4,
	TOTAL_MOTOR
}MOTOR_TYPE;
void MOTOR_Init(void);

void MOTOR_Stop(MOTOR_TYPE m);
void MOTOR_CW(MOTOR_TYPE m);
void MOTOR_CW2(MOTOR_TYPE m);
void MOTOR_CCW(MOTOR_TYPE m);
//speed 0:100
// 
//void MOTOR_Speed(MOTOR_TYPE m,u8 speed);
void Case_M1(void);
void Case_M2(void);
void Case_M3(void);
void Case_M4(void);




#endif /* MOTOR_INTERFACE_H_ */