#include <stdint.h>


#define FIXED_POINT_FRACTIONAL_BITS 24
#define magnetCount 8
#define torque 0
#define rpm 0


void getIntData(uint16_t speed, uint8_t* data);
void getCanData(uint8_t* rawData, int32_t* retData);
double getCanFloatData(uint8_t* data);
double fixed_to_float(int32_t input);
int getCanDataInt8(uint8_t* data);