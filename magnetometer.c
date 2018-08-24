#include "usi_i2c.h"
#include <msp430.h>
#include "magnetometer.h"



const uint32_t lookup[lookup_prec] = {1143,     3432,     5722,     8016,     10315,    12620,    14933,    17255,
                                      19588,    21933,    24292,    26666,    29057,    31467,    33897,    36349,
                                      38825,    41326,    43856,    46415,    49005,    51630,    54291,    56991,
                                      59732,    62518,    65350,    68231,    71166,    74156,    77207,    80321,
                                      83502,    86754,    90083,    93492,    96988,    100575,   104259,   108047,
                                      111946,   115962,   120105,   124382,   128804,   133379,   138121,   143039,
                                      148149,   153465,   159003,   164780,   170816,   177133,   183756,   190710,
                                      198028,   205741,   213890,   222516,   231668,   241404,   251786,   262889,
                                      274798,   287611,   301444,   316435,   332745,   350567,   370135,   391732,
                                      415707,   442491,   472630,   506817,   545954,   591227,   644239,   707201,
                                      783255,   877023,   995590,   1150404,  1361234,  1665427,  2143008,  3002042,
                                      5005437,  15019363};

const uint8_t shiftAmount = 17;

void magnetometer_normal() 
{
    // Give system an ODR of 2.5 Hz. X and Y in high power mode
    uint16_t setXY[] = {WRITE, CTRL_REG1, 0x48};
    // Set scale to be +- 4 guass. 
    uint16_t setSCALE[] = {WRITE, CTRL_REG2, 0x00};
    // Put system in continuous conversion mode 
    uint16_t setCConversion[] = {WRITE, CTRL_REG3, 0x00};
    // Put Z in low power mode
    uint16_t setZ[] = {WRITE, CTRL_REG4, 0x00};
    // Block data update - date will only be updated once it has been read
    uint16_t setBDU[] = {WRITE, CTRL_REG5, 0x40};

    /*
    uint16_t ctrl1_data = 0x48;
    uint16_t ctrl2_data = 0x00;
    uint16_t ctrl3_data = 0x00;
    uint16_t ctrl4_data = 0x00;
    uint16_t ctrl5_data = 0x40;

    uint16_t setSettings[] = {WRITE, (CTRL_REG1 | 0x80), ctrl1_data, ctrl2_data, ctrl3_data, ctrl4_data, ctrl5_data};
    i2c_send_sequence(setSettings, 7, 0, LPM0_bits);
    */

    i2c_send_sequence(setXY, 3, 0, LPM0_bits);
    i2c_send_sequence(setSCALE, 3, 0, LPM0_bits);
    i2c_send_sequence(setCConversion, 3, 0, LPM0_bits);
    i2c_send_sequence(setZ, 3, 0, LPM0_bits);
    i2c_send_sequence(setBDU, 3, 0, LPM0_bits);
}

void magnetometer_copy()
{
    // OM = 00 (low-power mode for X and Y); DO = 000 (0.625 Hz ODR)
    uint16_t setXY[] = {WRITE, CTRL_REG1, 0x70};
    // FS = 00 (+/- 4 gauss full scale)
    uint16_t setSCALE[] = {WRITE, CTRL_REG2, 0x00};
    // MD = 00 (continuous-conversion mode)
    uint16_t setCConversion[] = {WRITE, CTRL_REG3, 0x00};
    // OMZ = 0 (low-power mode for Z)
    uint16_t setZ[] = {WRITE, CTRL_REG4, 0x0C};
    // set this bdu
   // uint16_t setBDU[] = {WRITE, CTRL_REG5, 0x40};

    i2c_send_sequence(setXY, 3, 0, LPM0_bits);
    i2c_send_sequence(setSCALE, 3, 0, LPM0_bits);
    i2c_send_sequence(setCConversion, 3, 0, LPM0_bits);
    i2c_send_sequence(setZ, 3, 0, LPM0_bits);
    // i2c_send_sequence(setBDU, 3, 0, LPM0_bits);
}

void magnetometer_powerDown() 
{
    // puts the system in power down mode --> make sure it draws almost no current here
    uint16_t setPowerDown[] = {WRITE, CTRL_REG3, 0x02};
    i2c_send_sequence(setPowerDown, 3, 0, LPM0_bits);
}

void magnetometer_wakeUp()
{
	uint16_t setWakeUp[] = {WRITE, CTRL_REG3, 0x00};
	i2c_send_sequence(setWakeUp, 3, 0, LPM0_bits);
}



static uint16_t process_data(uint8_t rawData[])
{
    int32_t x = (int32_t) (rawData[1] << 8 | rawData[2]);
    int32_t y = (int32_t) (rawData[3] << 8 | rawData[4]);

    x = (x - X_OFFSET);
    y = (y - Y_OFFSET);
    y = y << shiftAmount;

    if (x == 0) return (y > 0) ? (90) : (270);

    int32_t quotient = ((x > 0) == (y > 0)) ? (y/x) : (-y/x);
    int16_t i;
    for (i = 0; i < lookup_prec; i++)
    {
      if (quotient < lookup[i]) break;
    }

    if ((x > 0) != (y > 0))
    {
        i = -i;
        if (x > 0) i += 360;
    }
    if (x < 0) i += 180;

    return (i == 360) ? (0) : (i);
}



uint16_t magnetometer_readData()
{
    uint8_t rawData[4]; // maybe this could be signed? the arduino library uses unsigned at this stage
    uint16_t readData[] = {WRITE, OUT_X_L, I2C_RESTART, READ, I2C_READ, I2C_READ, I2C_READ, I2C_READ};
    i2c_send_sequence(readData, 8, &rawData[0], LPM0_bits);
    uint16_t theta = process_data(rawData);
    return theta;

    // put theta at the end of the array
    // determine stability
    // return stability - maybe
}



uint8_t magnetometer_newData()
{
    uint8_t status;
    uint16_t readData[] = {WRITE, STATUS_REG, I2C_RESTART, READ, I2C_READ};
    i2c_send_sequence(readData, 5, &status, LPM0_bits);
    return (status & 0x01) && ((status >> 1) & (0x01));

    // int i = atan2(2,1);
}

