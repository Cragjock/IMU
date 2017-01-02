
#ifndef IMU_DEFINES_H
#define IMU_DEFINES_H


///  Gyro HPF
#define GYRO_HPF_0          0
#define GYRO_HPF_1          1
#define GYRO_HPF_2          2
#define GYRO_HPF_3          3
#define GYRO_HPF_4          4
#define GYRO_HPF_5          5
#define GYRO_HPF_6          6
#define GYRO_HPF_7          7
#define GYRO_HPF_8          8
#define GYRO_HPF_9          9
#define HP_EN               0x40    ///set bit 7
#define HP_DISABLE          0x00    /// clear bit 7

///  Mag MD
#define Mag_CONT        0
#define Mag_SINGLE      1
#define Mag_OM3         2
#define Mag_OM4         3


#define new_XL_data 1
#define new_G_data 2
#define new_XLG_data 3


#endif // IMU_DEFINES_H
