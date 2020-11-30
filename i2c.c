#include "compiler_defs.h"
#include "C8051F380_defs.h"
#include "i2c.h"
#include "initsys.h"

#define usec 20  // delay clk 1/2T

// Starts I2C serial transfer
void Wire_start(void)
{
	SDA=0;
	delay_us(usec);
	SCL=0;
}

// Stops I2C serial transfer 
void Wire_stop(void)
{
	SDA=0;
	SCL=1;
	delay_us(usec);
	SDA=1;
	delay_us(usec);
}


bit Wire_write(U8 outchar)
{
	bit ack;
	int i;
	// Write 8 bits 
	for(i=0;i<8;i++)
	{
		SDA=outchar & (0x80>>i);
	delay_us(usec);
		SCL=1;
	delay_us(usec); 
		SCL=0; 	
	}
	
	
	delay_us(usec);
	// Get ACK bit 
	SDA=1;
	SCL=1;
	delay_us(usec);
	ack=SDA;
//delay_us(usec);//////////////	
	SCL=0;
	delay_us(usec);
	return(ack);	
}


U8 Wire_read(bit ask_master) 
{
	U8 inchar=0;
int i;
	SDA=1;
for(i=0;i<8;i++)
	{
		SCL=1; 
		delay_us(usec);  
		//bit7_i2c=SDA;
    if(SDA) inchar=inchar|(0x80>>i)	;
		SCL=0;  
		delay_us(usec);
	}
	

	// Acknowledge sender if this is not the last byte. 
	SDA=ask_master;
	delay_us(usec);
	SCL=1;
	delay_us(usec); 
	SCL=0;
	delay_us(usec);
	return(inchar);
}




