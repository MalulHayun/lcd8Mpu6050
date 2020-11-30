
#ifndef _I2C_H
#define _I2C_H
#include "compiler_defs.h"
#include "C8051F380_defs.h"

/************************** I2C ********************************/
/***************************************************************/
/* use this bits to control which bits connected to the I2C bus */

sbit SDA=P0^7;               
sbit SCL=P0^6;
void Wire_start(void);
void Wire_stop(void);
bit Wire_write(unsigned char outchar);
unsigned char Wire_read(bit ask_master);

#endif



