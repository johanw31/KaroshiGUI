#include <stdint.h>


#define FIXED_POINT_FRACTIONAL_BITS 24

void getSpeedData(uint16_t speed, uint8_t* data);
int getCanData(uint8_t* data);
double getCanFloatData(uint8_t* data);
double fixed_to_float(int32_t input);