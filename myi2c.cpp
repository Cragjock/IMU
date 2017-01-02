
#include "myi2c.h"


const int myI2C_address[5]= {I2C_SLAVE_ADDR_IMU, 0x1c, 0x5c, 0x5f, 0x6f};
static const char * devName = "/dev/i2c-1";
static int I2C_Init(const char* devname, int sadrress);



/************************************/
/// I2C stuff
///

int I2C_Set(int slaveaddress)
{
    return I2C_Init(devName, slaveaddress);
}


static int I2C_Init(const char* devname, int slaveaddress)
{
    int myFP = open(devname, O_RDWR);       // device name= "/dev/i2c-1" how auto detect?
    if (myFP == -1)
        {
            perror(devname);
            exit(1);
        }
    if (ioctl(myFP, I2C_SLAVE, slaveaddress) < 0)
    //if (ioctl(myFP, I2C_SLAVE_FORCE, I2C_SLAVE_ADDR_MAG) < 0)
    {
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }
    return myFP;
}

/************************************/
///
int myI2C_read(int myFP, int reg_request)
{
    int result=i2c_smbus_read_byte_data(myFP, reg_request);
    if (result < 0)
        {
            perror("Failed to read from the i2c bus");
            exit(1);
        }
    return result;
}

/**********************************/
///
int myI2C_write(int myFP, int reg_request, int data)
{
    int result = i2c_smbus_write_byte_data(myFP, reg_request, data);
    if (result < 0)
        {
            perror("Failed to write to the i2c bus");
            exit(1);
        }
    return result;
}


/**********************************/
///
int myI2C_read_block(int myFP, int reg_request, int rd_size, unsigned char* readbuffer)
{
    int result = i2c_smbus_read_i2c_block_data(myFP, reg_request, rd_size, readbuffer);
    if(result < 0)
        {
            perror("Failed to read from the i2c bus");
            exit(1);
        }

    return result;
/// int result = i2c_smbus_read_block_data(I2C_FP[IMU], IMU_WHO_AM_I, read_buffer); NO GOOD  HERE
/// SMBus limits read of 32
}
