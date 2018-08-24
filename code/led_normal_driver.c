// #include <math.h>
#include <stdint.h>
#include <msp430.h>
#include <usi_i2c.h>
#include "led_normal_driver.h"

const uint8_t driverAddr[3] = {0xCE, 0xCA, 0xC6};
uint8_t driverLast = 0;

const uint16_t scaledBatteryVoltages[numLEDs] = {387, 442, 497, 553, 562, 571, 580, 590, 599, 608, 617,
                                                 626, 636, 645, 654, 672, 682, 691, 700, 719, 737, 755,
                                                 768, 774};


void writeAngle(uint16_t theta)
{
	theta /= degreesToLEDs;
	uint8_t ledIndex = theta % ledsPerDriver; 
	uint8_t driver = theta/ledsPerDriver;

	uint16_t data = 1 << ledIndex;

	uint16_t offLED[]   = {driverAddr[driverLast], regAddr, 0x00};
    uint16_t lightLED[] = {driverAddr[driver], regAddr, data};
    i2c_send_sequence(offLED, 3, 0, LPM0_bits);
    i2c_send_sequence(lightLED, 3, 0, LPM0_bits);

	driverLast = driver;

	// turn on driver




}




void writeBatteryStrength(uint16_t scaledBatteryVoltage)
{
    uint16_t numLitLEDs;
    for (numLitLEDs = 1; numLitLEDs < numLEDs; numLitLEDs++)
    {
        if (scaledBatteryVoltage <= scaledBatteryVoltages[numLitLEDs - 1]) break;
    }


    uint32_t data = ((uint32_t)1 << numLitLEDs) - 1;
    uint16_t lightLED0[3] = {driverAddr[0], regAddr, (data & 0x0000FF) >> 0};
    uint16_t lightLED1[3] = {driverAddr[1], regAddr, (data & 0x00FF00) >> 8};
    uint16_t lightLED2[3] = {driverAddr[2], regAddr, (data & 0xFF0000) >> 16};

    i2c_send_sequence(lightLED0, 3, 0, LPM0_bits);
    i2c_send_sequence(lightLED1, 3, 0, LPM0_bits);
    i2c_send_sequence(lightLED2, 3, 0, LPM0_bits);

}

void initializeNormalDrivers()
{
    uint16_t offLED0[3] = {driverAddr[0], regAddr, 0x00};
    uint16_t offLED1[3] = {driverAddr[1], regAddr, 0x00};
    uint16_t offLED2[3] = {driverAddr[2], regAddr, 0x00};

    i2c_send_sequence(offLED0, 3, 0, LPM0_bits);
    i2c_send_sequence(offLED1, 3, 0, LPM0_bits);
    i2c_send_sequence(offLED2, 3, 0, LPM0_bits);
}

