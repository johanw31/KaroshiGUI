#include <stdint.h>
#include "functions.h"
#include <iostream>

using namespace std;


union canData16 {
	int16_t int16Data;
	uint16_t uint16Data;
	uint8_t Data[2];
} canVal16;

union canData32 {
	int32_t int32Data;
	uint32_t uint32Data;
	uint8_t Data[4];
} canVal32;

double fixed_to_float(int32_t input)
{
	return ((double)input / (double)(1 << FIXED_POINT_FRACTIONAL_BITS));
}

void getSpeedData(uint16_t speed, uint8_t* data) {
	data[0] = (uint8_t)speed;
	data[1] = (uint8_t)(speed >> 8);
}

int getCanData(uint8_t* data) {
	canVal32.Data[3] = data[3];
	canVal32.Data[2] = data[2];
	canVal32.Data[1] = data[1];
	canVal32.Data[0] = data[0];
	return canVal32.int32Data;
}

double getCanFloatData(uint8_t* data) {
	canVal32.Data[3] = data[3];
	canVal32.Data[2] = data[2];
	canVal32.Data[1] = data[1];
	canVal32.Data[0] = data[0];
	cout << canVal32.int32Data << endl;
	return fixed_to_float(canVal32.int32Data);
}