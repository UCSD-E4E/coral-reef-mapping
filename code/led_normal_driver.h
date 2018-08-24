#define regAddr 0x44
#define numLEDs 24
#define ledsPerDriver 8
#define degreesToLEDs 15

#define ADCbits 10
// #define ADCToLEDs ((float) (numLEDs + 1))/(2 << 10)

void writeAngle(uint16_t theta);

void writeBatteryStrength(uint16_t strenth);

void initializeNormalDrivers();
