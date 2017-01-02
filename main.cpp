#include <iostream>
#include "IMU.h"

#include "myi2c.h"

using namespace std;


int I2C_FP[5];


int main()
{
    cout << "Hello world!" << endl;
    I2C_FP[IMU]=    I2C_Set(I2C_SLAVE_ADDR_IMU);
    I2C_FP[MAG]=    I2C_Set(I2C_SLAVE_ADDR_MAG);

    settings IMU_default= { M_ODR_10,       /// CRMAG 0x20
                            M_FSR_4,        /// CRMAG 0x21
                            Mag_CONT,       /// CRMAG 0x22
                            0.001234,
                            G_ODR_119,      /// CRG 0x10
                            G_FS_500,       /// CRG 0x10
                            G_BW_1,         /// CRG 0x10
                            GYRO_HPF_3,     /// CRG 0x12
                            0.0023,
                            XL_ODR_119,     /// CRXL 0x20
                            XL_FSR_2,       /// CRXL 0x20
                            BW_XL_50,       /// CRXL 0x20
                            XL_DCF_100,     /// CRXL 0x21
                            0.0547};
/************************************/

    IMU_set_config(&IMU_default);

    cout<<"settings "<<IMU_default<<endl;

    short IMUtemp = IMU_get_temperature();
    cout<<"IMU temp °C: "<<IMUtemp<<endl;

    int data_check = check_new_data(new_XLG_data);
    cout<<"data ready: "<<data_check<<endl;

    //int reg_value = myI2C_read(I2C_FP[IMU], WHO_AM_I);
    //cout<<"WHO_AM_I_XLG: "<<hex<<reg_value<<endl;
    //reg_value = myI2C_read(I2C_FP[MAG], WHO_AM_I);
    //cout<<"WHO_AM_I MAG: "<<hex<<reg_value<<endl;

    IMU_read();

    /// cleanup and close
    close(I2C_FP[IMU]);
    close(I2C_FP[MAG]);
    cout<<"good bye"<<endl;

    return 0;
}
