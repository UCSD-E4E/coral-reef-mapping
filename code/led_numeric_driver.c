#include <led_numeric_driver.h>
#include "usi_i2c.h"
#include <stdint.h>
#include <msp430.h>

const uint8_t digitRep[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0xFB};
static const uint16_t seaLevelPressure = 1013;

static void write_display(uint16_t value_one, uint8_t type)
{
    // Digit0 = least significant digit (lsd)
    // note that this will only work if the number is less than 9999

    // just test that this data makes sense - pushing on it a bit should yield two meters
    // and the decimal point should be there
    if (type == DEPTH) value_one -= seaLevelPressure;

    uint16_t value_ten = value_one/10;
    uint16_t value_hun = value_ten/10;
    uint16_t value_tho = value_hun/10;

    uint8_t digit3 = value_one - 10 * value_ten;
    uint8_t digit2 = value_ten - 10 * value_hun;
    uint8_t digit1 = value_hun - 10 * value_tho;
    uint8_t digit0 = value_tho;

    uint16_t writeAddr = (type == HEADING) ? (WRITE_ADDR_HEADING) : (WRITE_ADDR_DEPTH);

    uint16_t writeDigits0[] = {writeAddr, DIGIT_0, digitRep[digit0]};
    uint16_t writeDigits1[] = {writeAddr, DIGIT_1, digitRep[digit1]};
    uint16_t writeDigits2[] = {writeAddr, DIGIT_2, digitRep[digit2]};
    uint16_t writeDigits3[] = {writeAddr, DIGIT_3, digitRep[digit3]};

    i2c_send_sequence(writeDigits0, 3, 0, LPM0_bits);
    i2c_send_sequence(writeDigits1, 3, 0, LPM0_bits);
    i2c_send_sequence(writeDigits2, 3, 0, LPM0_bits);
    i2c_send_sequence(writeDigits3, 3, 0, LPM0_bits);
}

void write_heading(uint16_t value)
{
    write_display(value, HEADING);
}

void write_depth(uint16_t value)
{
    write_display(value, DEPTH);
}

static void initialize_driver(uint8_t type)
{
    uint16_t writeAddr = (type == HEADING) ? (WRITE_ADDR_HEADING) : (WRITE_ADDR_DEPTH);
    uint16_t numDigits = (type == HEADING) ? (THREE_DIGITS) : (FOUR_DIGITS);

    // Set PWM to max brightness, get out of shutdown mode, set # digits
    uint16_t settings[] = {writeAddr, PWM_REG, PWM_MAX, 0x03, NORMAL_OPERATION};
    i2c_send_sequence(settings, 5, 0, LPM0_bits);


    if (type == DEPTH)
    {
        const uint16_t decimal_point[] = {writeAddr, SEGMENT, DECIMAL_POINT};
        i2c_send_sequence(decimal_point, 3, 0, LPM0_bits);
    }

}

void initialize_heading_driver()
{
    initialize_driver(HEADING);
}

void initialize_depth_driver()
{
    initialize_driver(DEPTH);
}

void shutdown(uint8_t type)
{
    uint16_t writeAddr = (type == HEADING) ? (WRITE_ADDR_HEADING) : (WRITE_ADDR_DEPTH);
    uint16_t shutdown[] = {writeAddr, SHUTDOWN_REG, SHUTDOWN_MODE};
    i2c_send_sequence(shutdown, 3, 0, LPM0_bits);

}
