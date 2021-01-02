
#include "initsys.h"
#include "i2c.h"
#include "mpu6050.h"
#include <math.h>

float gyroScale = 131;  // gyro scale from datasheet

void Init_Device(void);
void Rotate(int angle);

int AccX, AccY, AccZ;
float  pitch, roll;
float wx,wy,wz;

void main()
{
	Init_Device();
	initSYS();

	config_mpu6050a(0x6B,0x0); //PWR_MGMT_1 register , set to zero (wakes up the MPU-6050)	
	LCD_setTextSize(3);
	LCD_printC(20,40,"Test mpu6050 ",3,WHITE);
	LCD_setText2Color(WHITE, BLACK);
	LCD_setTextSize(2);

	while(1)
	{
		//read 3-axis accelerometer
		AccX=read_mpu6050a(0x3B);
		AccY=read_mpu6050a(0x3D);
		AccZ=read_mpu6050a(0x3F);

		pitch = (180/3.141592) * atan((float)AccX / sqrt(pow((float)AccY,2) + pow((float)AccZ,2)));
		roll =  (180/3.141592) * atan((float)AccY / sqrt(pow((float)AccX,2) + pow((float)AccZ,2)));

		LCD_setCursor(0, 100);

		//display 3-axis acceleration & angle
		printf("ACCx=%d   \n",AccX);
		printf("ACCy=%d   \n",AccY);
		printf("ACCz=%d   \n",AccZ);
		printf("\n");

		printf("roll=%d pitch=%d         \n",(int)roll,(int)pitch);
		delay_ms(100);
		
		wx=read_mpu6050a(0x43);
		wy=read_mpu6050a(0x45);
		wz=read_mpu6050a(0x47);

		printf("wx=%d   \n",(int)wx);
		printf("wy=%d   \n",(int)wy);
		printf("wz=%d   \n",(int)wz);

	}
}




