
#ifndef MY_I2C_H
#define MY_I2C_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include <poll.h>
#include <signal.h>

/// I2C slave address
#define I2C_SLAVE_ADDR_RTC      0x6f        /// TBD
#define I2C_SLAVE_ADDR_IMU      0x6a        /// MEMS LSM9DS1
#define I2C_SLAVE_ADDR_MAG      0x1c        /// MEMS LSM9DS1
#define I2C_SLAVE_ADDR_RHTEMP   0x5f        /// MEMS HTS221
#define I2C_SLAVE_ADDR_PRESSURE 0x5c        /// MEMS LP25H

#define READ_BUF_G         0x00
#define READ_BUF_XL        0x08

extern int I2C_FP[5];
enum I2C_bus {IMU, MAG, TEMP, HUMID, RTC};  /// add others for future

int I2C_Set(int slaveaddress);

int myI2C_read(int whoaddress,int RTC_reg);

int myI2C_write(int whpaddress, int RTC_reg, int data);

int myI2C_read_block(int myFP, int reg_request, int rd_size, unsigned char* readbuffer);

int myI2C_read_index(int index);

int myI2C_write_index(int index);




#endif // MY_I2C_H
