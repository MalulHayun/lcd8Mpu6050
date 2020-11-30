
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
char str[40];

//sbit pin=P2^7;

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
		LCD_setCursor(5, 200);
		LCD_print("   ");	
		LCD_setTextSize(1);
		Rotate(90);
		LCD_setTextSize(2);
		delay_ms(100);

		/*
		wx=read_mpu6050a(0x43)/gyroScale;
		wy=read_mpu6050a(0x45)/gyroScale;
		wz=read_mpu6050a(0x47)/gyroScale;

		sprintf(str,"%d     ",(int)wx);
		LCD_print2C(10,50,str,2,BLACK,WHITE);

		sprintf(str,"%d    ",(int)wy);
		LCD_print2C(10,100,str,2,BLACK,WHITE);

		sprintf(str,"%d     ",(int)wz);
		LCD_print2C(10,150,str,2,BLACK,WHITE);

		angleZ = angleZ + dt * wz  / 1000  ; //integral Calculate angle, 1000(ms -> s)	

		sprintf(str,"%d     ",(int)angleZ);
		LCD_print2C(10,200,str,2,BLACK,WHITE);
		*/



	}
}



void Rotate(int angle)
{
	float wz,anglez;

	anglez=0;
	//	if(angle>0)
	//		motors(130,-130);
	//	else if(angle<0)
	//		motors(-130,130);

	while(1)
	{
		TF0=0;
		TL0=-60000;    
		TH0=(-60000)>>8;
		TR0=1;
		//pin=1;
		//read z, axis from gyro
		wz=read_mpu6050a(0x47)/gyroScale; //deg/sec
		//Integral

		anglez=anglez+(wz*0.015);//15msec=dt

		if((angle<0)&&(angle>anglez))break;
		if((angle>0)&&(angle<anglez))break;
		LCD_setCursor(5, 200);

		printf("%d  ",(int)anglez);
		//pin=0;

		while(!TF0);// wait 15msec
		TR0=0;

	}	
	TR0=0;

	//motors(0,0);
}




