
//mpu6050a 
//3-axis accelerometer 
#include "compiler_defs.h"
#include "C8051F380_defs.h"
#include "i2c.h"

#define MPU6050_address 0x68  // 110_1000

bit config_mpu6050a(unsigned char add,unsigned char outchar)
{
	bit ask=1;
	Wire_start();
	if(!Wire_write(MPU6050_address<<1 )); //  Write  pin12=0
	{
		ask=Wire_write(add);
		ask=Wire_write(outchar);
	}
	Wire_stop();
	return ask; //if ask=0 data ok
}


int read_mpu6050a(unsigned char add)  // read 2 byte
{

	unsigned int in_int = 0;
	Wire_start();
	if(!Wire_write(MPU6050_address<<1)); //  Read  pin11=0
	{
		Wire_write(add);

		Wire_stop();
		Wire_start();
		//  Read data 
		Wire_write((MPU6050_address<<1) | 1);  
		in_int=Wire_read(0)<<8;  //0-  ack from master 
		in_int|=Wire_read(1);  //1- read byte and finish no ack
	}
	Wire_stop();
	return in_int;	
}



