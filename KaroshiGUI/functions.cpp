#include <stdint.h>
#include "functions.h"
#include <iostream>

using namespace std;

/*
* Die Funktionen dienen nur zum umrechnen der CanBus Daten in die entsprechende Größen.
* Diese sind hauptsächlich testweise und beim debuggen entstanden. Somit werden nicht mehr alle verwendet
*/

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

void getIntData(uint16_t speed, uint8_t* data) {
	data[0] = (uint8_t)speed;
	data[1] = (uint8_t)(speed >> 8);
}

void getCanData(uint8_t* rawData, int32_t* retData) {
	canVal32.Data[3] = rawData[1];
	canVal32.Data[2] = rawData[0];
	canVal32.Data[1] = 0;
	canVal32.Data[0] = 0;
	retData[0] = canVal32.int32Data >> 16;
	canVal32.Data[3] = rawData[3];
	canVal32.Data[2] = rawData[2];
	canVal32.Data[1] = 0;
	canVal32.Data[0] = 0;
	retData[1] = canVal32.int32Data >> 16;
}

double getCanFloatData(uint8_t* data) {
	canVal32.Data[3] = data[3];
	canVal32.Data[2] = data[2];
	canVal32.Data[1] = data[1];
	canVal32.Data[0] = data[0];
	cout << canVal32.int32Data << endl;
	return fixed_to_float(canVal32.int32Data);
}

int getCanDataInt8(uint8_t* data) {
	return (int8_t)data * (-1);
}