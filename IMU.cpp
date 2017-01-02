#include <iostream>
#include "IMU.h"
#include "IMUregname.h"
#include "myi2c.h"

using namespace std;

unsigned char XLG_read_buffer[36];
unsigned char M_read_buffer[36];


/***************************/
/// temperature register, see spec pg 14
/// 16°C/LSB,  sensor out is 0 at 25 degC
    short IMU_get_temperature()
    {

        unsigned char temp_read_buffer[4];
        int result= myI2C_read_block(I2C_FP[IMU], OUT_TEMP_L, 2, temp_read_buffer);
        short buftemp = short((temp_read_buffer[temp_LB] | (temp_read_buffer[temp_HB]<<8)));
        buftemp = buftemp/16;
        buftemp = buftemp+25;
        //printf("is this the temp? %i degress C\n", buftemp);
        cout<<"temp °C: "<<buftemp<<"\n"<<endl;
        return buftemp;
    }

/***********************************/
/// LSM9DS1 set based on IMUset
void IMU_set_config(settings* IMUset)
{
     cout<<"in set defaults"<<"\n"<<endl;
     int cr_data=-1;

/// CTRL_REG1_G reg 0x10, ODR | FS | BW
    cr_data = IMUset->gyro_ODR | IMUset->gyro_FS | IMUset->gyro_BW;
    myI2C_write(I2C_FP[IMU], CTRL_REG1_G, cr_data);

    switch(IMUset->gyro_FS)
    {
        case G_FS_245:
            IMUset->gyro_sensitivity = .00875;
            break;
        case G_FS_500:
            IMUset->gyro_sensitivity = .00875;
            break;
        case G_FS_1200:
            IMUset->gyro_sensitivity = .00875;
            break;
        default:
            IMUset->gyro_sensitivity =0.0;
    }





/// CTRL_REG6_XL reg 0x20, ODR | FS | BW
    cr_data = IMUset->XL_ODR | IMUset->XL_FS | IMUset->XL_BW;
    myI2C_write(I2C_FP[IMU], CTRL_REG6_XL, cr_data);

/// CTRL_REG3_G reg 0x12, HP_EN | HPCF
//    cr_data = HP_EN | GYRO_HPF_3;
//    myI2C_write(I2C_FP[IMU], CTRL_REG3_G, cr_data);

/// CTRL_REG7_XL reg 0x21, DCF
    cr_data = IMUset->XL_DCF;
    myI2C_write(I2C_FP[IMU], CTRL_REG7_XL, cr_data);

/// CTRL_REG1_M reg 0x20,
    cr_data = IMUset->mag_ODR | 0xa0;
    myI2C_write(I2C_FP[MAG], CTRL_REG1_M, cr_data);

/// CTRL_REG2_M reg 0x21,
    cr_data = IMUset->mag_FS;
    myI2C_write(I2C_FP[MAG], CTRL_REG2_M, cr_data);

/// CTRL_REG3_M reg 0x22,
    cr_data = IMUset->mag_DM;
    myI2C_write(I2C_FP[MAG], CTRL_REG3_M, cr_data);

/***********************************
    m_LSM9DS1GyroSampleRate = LSM9DS1_GYRO_SAMPLERATE_119;
    m_LSM9DS1GyroBW = LSM9DS1_GYRO_BANDWIDTH_1;
    m_LSM9DS1GyroHpf = LSM9DS1_GYRO_HPF_4;
    m_LSM9DS1GyroFsr = LSM9DS1_GYRO_FSR_500;

    m_LSM9DS1AccelSampleRate = LSM9DS1_ACCEL_SAMPLERATE_119;
    m_LSM9DS1AccelFsr = LSM9DS1_ACCEL_FSR_8;
    m_LSM9DS1AccelLpf = LSM9DS1_ACCEL_LPF_50;

    m_LSM9DS1CompassSampleRate = LSM9DS1_COMPASS_SAMPLERATE_20;
    m_LSM9DS1CompassFsr = LSM9DS1_COMPASS_FSR_4;
**************************************/

}

/*******************************/
/// new data check
int check_new_data(int data)
{
    int result = -1;
    result= (myI2C_read(I2C_FP[IMU], STATUS_REG)) & data;
    return result;
}

/*******************************/
/// read the data
/// assumes init is done etc.
int IMU_read()
{
    int result = -1;
    unsigned char gyro_data[6];
    unsigned char accel_data[6];
    unsigned char mag_data[6];

    result= myI2C_read_block(I2C_FP[IMU], OUT_X_L_G, 6, gyro_data);
    result= myI2C_read_block(I2C_FP[IMU], OUT_X_L_XL, 6, accel_data);
    result= myI2C_read_block(I2C_FP[MAG], OUT_X_L_M, 6, mag_data);



    return 0;
}

int IMU_data_convert(unsigned char* data)
{

/********************************************

    GYRO.x_LB = XLG_read_buffer[gx_LB];
    GYRO.x_UB = XLG_read_buffer[gx_HB];
    GYRO.y_LB = XLG_read_buffer[gy_LB];
    GYRO.y_UB = XLG_read_buffer[gy_HB];
    GYRO.z_LB = XLG_read_buffer[gz_LB];
    GYRO.z_UB = XLG_read_buffer[gz_HB];

    GYRO.x = (GYRO.x_UB<<8) | GYRO.x_LB;
    GYRO.y = (GYRO.y_UB<<8) | GYRO.y_LB;
    GYRO.z = (GYRO.z_UB<<8) | GYRO.z_LB;

    float G_offset = 0.00;

    float myGX = (float)GYRO.x * G_So[myConfig.gyro_FS] + G_offset;
    float myGy = (float)GYRO.y * G_So[myConfig.gyro_FS] + G_offset;
    float myGz = (float)GYRO.z * G_So[myConfig.gyro_FS] + G_offset;
****************************/
return 0;

}







ostream& operator<< ( ostream& os, settings& mySet)
{
    os<<"G FS: "<<mySet.gyro_sensitivity
        <<"\tXL FS: "<<mySet.XL_sensitivity
        <<"\tMag FS: "<<mySet.mag_sensitivity;as<<endl;
	return os;
}








