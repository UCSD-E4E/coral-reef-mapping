#include <msp430.h>
#include "usi_i2c.h"
#include "depth_sensor.h"

const uint8_t numCoefficients = 6;
uint16_t coefficients[6];

void depthSensor_reset()
{
    uint8_t i;
    uint16_t reset[] = {WRITE_ADDRESS, RESET};
    i2c_send_sequence(reset, 2, 0, LPM0_bits);
    int j = 0;
    while (j < 100)
    {
        j++;
    }
    uint8_t dataBytes[2];
    uint16_t readCoefficient[] = {WRITE_ADDRESS, START_COEFFICIENT, I2C_RESTART, READ_ADDRESS, I2C_READ, I2C_READ};
    for (i = 0; i < numCoefficients; i++)
    {
        i2c_send_sequence(readCoefficient, 6, &dataBytes[0], LPM0_bits);
        coefficients[i] = (dataBytes[0] << 8) | dataBytes[1];
        readCoefficient[1] += 2;
    }
}



int32_t depthSensor_pressure()
{
    int32_t pressure = realPressure()/100;
    return pressure;
}

static uint32_t readRawData(uint16_t typeAddress)
{
    uint8_t dataBytes[3];
    uint32_t rawData;

    uint16_t convertData[] = {WRITE_ADDRESS, typeAddress};
    uint16_t readADC[] = {WRITE_ADDRESS, READ_ADC, I2C_RESTART, READ_ADDRESS, I2C_READ, I2C_READ, I2C_READ};

    i2c_send_sequence(convertData, 2, 0, LPM0_bits);
    int i = 0;
    while (i < 1000)
    {
        i++;
    }
    i2c_send_sequence(readADC, 7, &dataBytes[0], LPM0_bits);
    rawData = ((uint32_t)dataBytes[0] << 16) + ((uint32_t)dataBytes[1] << 8) + dataBytes[2];
    return rawData;

}



static int32_t realPressure()
{
    //Retrieve ADC result
    int32_t temperature_raw = readRawData(CONVERT_TEMP);
    int32_t pressure_raw = readRawData(CONVERT_PRESSURE);


    //Create Variables for calculations
    int32_t temp_calc;
    int32_t pressure_calc;

    int32_t dT;

    //Now that we have a raw temperature, let's compute our actual.
    dT = temperature_raw - ((int32_t)coefficients[4] << 8);
    temp_calc = (((int64_t)dT * coefficients[5]) >> 23) + 2000;

    // TODO TESTING  _temperature_actual = temp_calc;

    //Now we have our first order Temperature, let's calculate the second order.
    int64_t T2, OFF2, SENS2, OFF, SENS; //working variables

    if (temp_calc < 2000)
    // If temp_calc is below 20.0C
    {
        T2 = 3 * (((int64_t)dT * dT) >> 33);
        OFF2 = 3 * ((temp_calc - 2000) * (temp_calc - 2000)) / 2;
        SENS2 = 5 * ((temp_calc - 2000) * (temp_calc - 2000)) / 8;

        if(temp_calc < -1500)
        // If temp_calc is below -15.0C
        {
            OFF2 = OFF2 + 7 * ((temp_calc + 1500) * (temp_calc + 1500));
            SENS2 = SENS2 + 4 * ((temp_calc + 1500) * (temp_calc + 1500));
        }
    }
    else
    // If temp_calc is above 20.0C
    {
        T2 = 7 * ((uint64_t)dT * dT)/(((uint64_t)2) << 36);
        OFF2 = ((temp_calc - 2000) * (temp_calc - 2000)) / 16;
        SENS2 = 0;
    }

    // Now bring it all together to apply offsets

    OFF = ((int64_t)coefficients[1] << 16) + (((coefficients[3] * (int64_t)dT)) >> 7);
    SENS = ((int64_t)coefficients[0] << 15) + (((coefficients[2] * (int64_t)dT)) >> 8);

    // temp_calc = temp_calc - T2;
    OFF = OFF - OFF2;
    SENS = SENS - SENS2;

    // Now lets calculate the pressure


    return (pressure_calc = (((SENS * pressure_raw) / 2097152 ) - OFF) / 32768);




}
