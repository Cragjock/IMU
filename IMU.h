
#ifndef IMU_H
#define IMU_H

using namespace std;

#include "IMUregname.h"
#include "IMUdefines.h"

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

/*****************************************/
/// Gyro settings
///
enum ODR_G {G_power_down=0,
            G_ODR_14_9=0x20,
            G_ODR_59_5=0x40,
            G_ODR_119=0x60,
            G_ODR_238=0x80,
            G_ODR_476=0xA0,
            G_ODR_952=0xC0};

enum FS_G { G_FS_245=0,
            G_FS_500=0x08,
            G_FS_NA=0x10,
            G_FS_1200=0x18};

enum BW_G {G_BW_0, G_BW_1, G_BW_2, G_BW_3};

/*****************************************/
/// acceleratometer settings
///
enum ODR_XL {   XL_power_down=0,
                XL_ODR_10=0x20,
                XL_ODR_50=0x40,
                XL_ODR_119=0x60,
                XL_ODR_238=0x80,
                XL_ODR_476=0xA0,
                XL_ODR_952=0xC0};

enum FS_XL {    XL_FSR_2=0,
                XL_FSR_16=0x08,
                XL_FSR_4=0x10,
                XL_FSR_8=0x18};
enum BW_XL {BW_XL_408, BW_XL_211, BW_XL_105, BW_XL_50 };

enum XL_DCF {   XL_DCF_50,
                XL_DCF_100,
                XL_DCF_9,
                XL_DCF_400};

/*****************************************/
/// magnetomoter settings
///
enum MAG_ODR {  M_ODR_625=0x00,
                M_ODR_125=0x04,
                M_ODR_25=0x08,
                M_ODR_5=0x0c,
                M_ODR_10=0x10,
                M_ODR_20=0x14,
                M_ODR_40=0x18,
                M_ODR_80=0x1c};

enum MAG_FS {   M_FSR_4=0x00,
                M_FSR_8=0x20,
                M_FSR_12=0x40,
                M_FSR_16=0x60};

/*****************************************/
/// sensitvities per spec, need access to these items
const float XL_So[]     = { 0.000061, 0.000732, 0.000122, 0.000244};
const float G_So[]      = {.00875, .01750, 0.70};
const float M_GN[]      = {0.00014, 0.00029, 0.00043, 0.00058 };


typedef struct tag_config
{
    int mag_ODR;    ///M_CR 0x20
    int mag_FS;     ///M_CR 0x21
    int mag_DM;     ///M_CR 0x22
    float mag_sensitivity;

    int gyro_ODR;   ///G_CR 0x10
    int gyro_FS;    ///G_CR 0x10
    int gyro_BW;    ///G_CR 0x10
    int gyro_HPF;   ///G_CR 0x12
    float gyro_sensitivity;

    int XL_ODR;     /// XL_CR 0x20
    int XL_FS;      /// XL_CR 0x20
    int XL_BW;      /// XL_CR 0x20
    int XL_DCF;     /// XL_CR 0x21
    float XL_sensitivity;

} settings;



typedef struct tag_DCM
{
    float x;    /// x component in, x angle out
    float y;    /// y component in, y angle out
    float z;    /// z component in, z angle out
    float r;    /// magnitude of x, y, z out
} DCM;




    enum buf_offset
    {
        temp_LB=0,
        temp_HB,
        gx_LB=0,
        gx_HB,
        gy_LB,
        gy_HB,
        gz_LB,
        gz_HB,
        xx_LB,
        xx_HB,
        xy_LB,
        xy_HB,
        xz_LB,
        xz_HB,
        mx_LB=0,
        mx_HB,
        my_LB,
        my_HB,
        mz_LB,
        mz_HB
    };


short IMU_get_temperature();
void IMU_set_config(settings*);
int check_new_data(int data);
int IMU_read(void);
int IMU_data_convert(unsigned char* data);
ostream& operator<< ( ostream& os, settings& mySet);

#endif // IMU_H
