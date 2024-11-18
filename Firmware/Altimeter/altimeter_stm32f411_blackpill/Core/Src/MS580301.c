/*
 * ms5.c
 *
 *  Created on: Feb 17, 2023
 *      Author: emils
 */
#include "MS580301.h"
#include "math.h"


float MS580301_Sea_Level_Pressure = 1013;
/*
 * Private functions
 */
static void MS580301_WriteCommand(MS580301* sensor, uint8_t command)
{
	HAL_I2C_Master_Transmit(sensor -> hi2c, sensor -> address, &command, 1, HAL_MAX_DELAY);
}

static uint16_t MS580301_ReadData(MS580301* sensor, uint8_t command)
{
	uint8_t data[2];
	HAL_I2C_Master_Transmit(sensor->hi2c, sensor-> address, &command, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(sensor->hi2c, sensor-> address, data, 2, HAL_MAX_DELAY);
	return (data[0] << 8) | data[1];
}

// Public functions

void MS580301_Init(MS580301* sensor, I2C_HandleTypeDef* hi2c)
{
	sensor->hi2c = hi2c;
	sensor->address = MS580301_I2C_ADDRESS;
	MS580301_Reset(sensor);
}

void MS580301_ReadCalibrationData(MS580301 *sensor)
{
	uint8_t buffer[2];
	uint16_t coefficients[7];

	// Read the calibration data
	for (int i = 0; i<7; i++)
	{
		HAL_I2C_Mem_Read(sensor->hi2c, sensor->address, 0xA2 + i *2, I2C_MEMADD_SIZE_8BIT, buffer, 2, 100);
		coefficients[i] = ((uint16_t)buffer[0] << 8) | buffer[1];
	}
	sensor->C1 = (float)coefficients[0];
	sensor->C2 = (float)coefficients[1];
	sensor->C3 = (float)coefficients[2];
	sensor->C4 = (float)coefficients[3];
	sensor->C5 = (float)coefficients[4];
	sensor->C6 = (float)coefficients[5];
}


void MS580301_Reset(MS580301* sensor)
{
	MS580301_WriteCommand(sensor, 0x1E);
	HAL_Delay(10);
}



void MS580301_ReadSensorData(MS580301* sensor, uint32_t* pressure, uint32_t* temperature)
{
	//read temperature
	MS580301_WriteCommand(sensor, 0x48);
	HAL_Delay(10);
	uint32_t rawTemperature = MS580301_ReadData(sensor, 0x00);

	// read pressure
	MS580301_WriteCommand(sensor, 0x58);
	HAL_Delay(10);
	uint32_t rawPressure = MS580301_ReadData(sensor, 0x00);




// Calculate compensated temperature and pressure
int32_t dT = (int32_t)rawTemperature - ((int32_t)sensor ->c [5] << 8);
int32_t offset1 = ((int32_t)sensor -> c[2] << 16) + ((int32_t) sensor -> c[4] * dT)  /128;
int32_t sens = ((int32_t)sensor ->c[1] << 15) + ((int32_t)sensor -> c[3] * dT) / 256;
*temperature = 2000 + ((int32_t)dT * sensor ->c[6]) / 8388608;
int32_t t2 = 0;
int32_t offset2 = 0;
int32_t sens2 = 0;
if (*temperature < 2000)
	{
		t2 = (int32_t)dT * dT / 2147483648;
		offset2 = 5* ((*temperature -2000) * (*temperature - 2000)) / 2;
		sens2 = 5 * ((*temperature - 2000) * (*temperature - 2000)) / 8;
		if (*temperature < -1500)
		{
			offset2 = offset2 + 7 * ((*temperature + 1500) * (*temperature + 1500));
			sens2 = sens2 + 4 * ((*temperature + 1500) * (*temperature + 1500));
		}
		*temperature = *temperature - t2;
		offset1 = offset1 - offset2;
		sens = sens - sens2;
	}
	*pressure = ((rawPressure * sens) / 2097152 - offset1) / 32768;
}


//Calculations

float MS580301_CalculateAltitude(MS580301* sensor, uint32_t pressure)
{
	float altitude = (1 - powf((float)pressure / MS580301_Sea_Level_Pressure, 0.1903f)) * 44330.0f;
	//float altitude = (1 - powf((float)pressure / MS580301_Sea_Level_Pressure));
	return altitude;
}




