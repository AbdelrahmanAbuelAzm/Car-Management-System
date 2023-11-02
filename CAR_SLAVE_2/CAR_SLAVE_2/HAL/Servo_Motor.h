
#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_


typedef enum{
	Door_Open =180,
	Door_Close =0
	
	}CAR_DOOR_STATUS_t;
	
typedef enum{
	Door_1 =0,
	Door_2 =1
		
	}CAR_DOOR_NO_t;
	
void Servo_SetAngle(u8 angle);
CAR_DOOR_STATUS_t Car_Door_Command(CAR_DOOR_NO_t door_num,CAR_DOOR_STATUS_t Previous_Servo_Angle,u8 OUT_PIN);


#endif /* SERVO_MOTOR_H_ */