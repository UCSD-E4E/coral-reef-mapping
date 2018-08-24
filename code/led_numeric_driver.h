#include "usi_i2c.h"

#include <msp430.h>

enum ledMultAddr
{
    WRITE_ADDR_DEPTH   = 0x70,
    WRITE_ADDR_HEADING = 0x70,

    DECODE_REG     = 0x01,
    PWM_REG        = 0x02,
    PICK_DIGIT_REG = 0x03,
    SHUTDOWN_REG   = 0x04,

    DIGIT_0 = 0x20,
    DIGIT_1 = 0x21,
    DIGIT_2 = 0x22,
    DIGIT_3 = 0x23,
    SEGMENT = 0x24,

    PWM_MAX      = 0x3F,
    FOUR_DIGITS  = 0x03,
    THREE_DIGITS = 0x02,
    NORMAL_OPERATION = 0x01,
    SHUTDOWN_MODE    = 0x00,
    DECIMAL_POINT    = 0x20,
    NO_DECIMAL    = 0x00,
};

enum infoType
{
    HEADING = 0,
    DEPTH   = 1,
};


void write_heading(uint16_t value);
void write_depth(uint16_t value);

void initialize_heading_driver();
void initialize_depth_driver();


void shutdown(uint8_t type);
