// #ifndef MAGNETOMETER_H
// #define MAGNETOMETER_H

// #include <msp430.h>
#include <stdint.h>

#define lookup_prec 90

enum magAddr
{
    WRITE       = 0x3C, // Address < 1
    READ        = 0x3D, // Address < 1 + 1

    // WHO_AM_I    = 0x0F,
    CTRL_REG1   = 0x20,
    CTRL_REG2   = 0x21,
    CTRL_REG3   = 0x22,
    CTRL_REG4   = 0x23,
    CTRL_REG5   = 0x24,

    STATUS_REG  = 0x27,
    OUT_X_L     = 0x28,
    OUT_X_H     = 0x29,
    OUT_Y_L     = 0x2A,
    OUT_Y_H     = 0x2B,
    OUT_Z_L     = 0x2C,
    OUT_Z_H     = 0x2D, 
    TEMP_OUT_L  = 0x2E,
    TEMP_OUT_H  = 0x2F,
    INT_CFG     = 0x30,
    INT_SRC     = 0x31,
    INT_THS_L   = 0x32,
    INT_THS_H   = 0x33,
};


enum dataOffset
{
    X_OFFSET = -1509,// -3431,
    Y_OFFSET = 1432,//900,
    X_OVER_Y_SCALE = 100,
};

enum powerMode
{
    LOW_POWER = 0,
    MEDIUM_POWER = 1,
    HIGH_POWER = 2,
    ULTRA_HIGH_POWER = 3,
};

enum onOff
{
    NORMAL_ON = 0x00,
    POWER_DOWN = 0x02,
};


void magnetometer_normal(uint8_t power_mode);
void magnetometer_powerDown();
void magnetometer_wakeUp();
uint16_t magnetometer_readData();
uint8_t magnetometer_newData();






// #endif
