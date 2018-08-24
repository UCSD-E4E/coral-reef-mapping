#include <led_numeric_driver.h>
#include <magnetometer.h>
#include <msp430.h>
#include "usi_i2c.h"
#include "depth_sensor.h"
//#include <stdint.h>
#include "led_normal_driver.h"
#include "read_adc.h"

void msp_init();
void waitForStability();
void waitForInstability();
void initializeDevices();
//void waitMagFlashLights();

uint16_t averageTheta;
uint16_t averagePressure;
uint16_t theta;

int main()
{

    uint16_t currentTheta;
    uint16_t currentPressure;

    uint16_t batStrength;
    uint8_t lightsOn = 1;

    initializeDevices();

   /*
   waitForStability();
   waitForInstability();
    // waitMagFlashLights();

    while(1)
    {
        while (!magnetometer_newData()){;}
        theta = magnetometer_readData();
        write_depth(averagePressure);
        lightsOn = lightsOn ? 0 : 1;
        writeBatteryStrength(lightsOn ? 1000 : 0);
       }
       */

    while (1)
    {
        batStrength = adc_read();
        if (batStrength > 100)
        {
            writeBatteryStrength(batStrength);
        }
        else
        {
            while (!magnetometer_newData()){;}
            currentTheta = magnetometer_readData();
            currentPressure = depthSensor_pressure();
            initializeNormalDrivers();
            writeAngle(currentTheta);
            write_heading(currentTheta);
        }

    }


}


void msp_init()
{
  volatile unsigned int i;                  // Use volatile to prevent removal

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
  {
    while(1);                               // do not load, trap CPU!!
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;

  P1OUT = 0xC0;                             // P1.6 & P1.7 Pullups, others to 0
  P1REN |= 0xC0;                            // P1.6 & P1.7 Pullups
  P1DIR = 0xFF;                             // Unused pins as outputs
  P2OUT = 0;
  P2DIR = 0xFF;

  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_1;                       // input A1
  ADC10AE0 |= 0x02;                         // PA.1 ADC option select
}


void waitForStability()
{
    uint16_t stableDataCount = 0;
    const uint16_t requiredCount = 10;
    uint16_t baseTheta;
    uint16_t currentTheta;
    int16_t error;
    const int16_t errorThreshold = 30;
    uint8_t lightsOn = 0;

    // uint16_t allowedOutlier

    while (!magnetometer_newData()){;}
    baseTheta = magnetometer_readData();
    while (stableDataCount < requiredCount)
    {
        writeBatteryStrength(lightsOn ? 1000 : 0);
        while (!magnetometer_newData()){;}
        lightsOn = lightsOn ? 0 : 1;
        currentTheta = magnetometer_readData();
        error = baseTheta - currentTheta;
        if (error > errorThreshold || error < -errorThreshold)
        {
            stableDataCount = 0;
            baseTheta = currentTheta;
        }
        else
        {
            stableDataCount++;
        }
    }

    averageTheta = currentTheta;
    averagePressure = depthSensor_pressure();
    initializeNormalDrivers();
}


void waitForInstability()
{
    uint16_t currentTheta = 0;
    int32_t  currentPressure = 0;


    uint16_t measurementCount = 1;

    uint32_t sumTheta = averageTheta;
    uint32_t sumPressure = averagePressure;

    int16_t error;
    const int16_t errorThreshold = 25;

    //while (!magnetometer_newData())
    while(1)
    {
        while (!magnetometer_newData()){;}
        measurementCount++;
        currentTheta = magnetometer_readData();
        currentPressure = depthSensor_pressure();

        error = averageTheta - currentTheta;
        if (error > errorThreshold || error < -errorThreshold)
        {
            break;
        }
        else
        {
            sumTheta += currentTheta;
            sumPressure += currentPressure;
            averageTheta = sumTheta/measurementCount;
            averagePressure = sumPressure/measurementCount;

            writeAngle(averageTheta);
            //write_heading(averageTheta);
            write_depth(averagePressure);
        }
    }
}
/*
void waitMagFlashLights()
{
    uint16_t lightCounter = 0;
    uint8_t lightsOn = 1;
    const uint16_t lightCounterMax = 5000;

    writeBatteryStrength(lightsOn ? 1000 : 0);
    while (!magnetometer_newData())
    {
        lightCounter++;
        if (lightCounter == lightCounterMax)
        {
            lightsOn = lightsOn ? 0 : 1;
            writeBatteryStrength(lightsOn ? 1000 : 0);
            lightCounter = 0;
        }
    }
}
*/
/*
void waitMagFlashLights(uint8_t lightsOn)
{
    writeBatteryStrength(lightsOn ? 1000 : 0);
    while (!magnetometer_newData()){;}
}
*/

void initializeDevices()
{
    msp_init();
    i2c_init(USIDIV_5, USISSEL_2);

    magnetometer_normal(ULTRA_HIGH_POWER);
    initializeNormalDrivers();
    initialize_heading_driver();
    // initialize_depth_driver();
    depthSensor_reset();
}

