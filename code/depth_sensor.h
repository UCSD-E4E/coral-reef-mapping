/*
 * depth_sensor.h
 *
 *  Created on: Aug 20, 2018
 *      Author: kastner-vr
 */

#ifndef DEPTH_SENSOR_H_
#define DEPTH_SENSOR_H_

enum depth_sensor_addresses
{
    WRITE_ADDRESS    = 0xEC,
    READ_ADDRESS     = 0xED,

    RESET             = 0x1E,
    CONVERT_PRESSURE  = 0x44,
    CONVERT_TEMP      = 0x54,
    READ_ADC          = 0x00,
    START_COEFFICIENT = 0xA2,
};

void depthSensor_reset();

int32_t depthSensor_pressure();

static int32_t realPressure();


#define pressureToDepth 1



#endif /* DEPTH_SENSOR_H_ */
