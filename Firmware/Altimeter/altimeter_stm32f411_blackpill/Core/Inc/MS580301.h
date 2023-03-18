/*
 * ms5.h
 *
 *  Created on: Feb 17, 2023
 *      Author: emils
 */

#ifndef INC_MS580301_H_
#define INC_MS580301_H_

#include "stm32f4xx_hal.h"


#define MS580301_I2C_ADDRESS 	0x76 //CBS setting high

typedef struct
{
	I2C_HandleTypeDef* hi2c;
	uint8_t address;
	uint16_t c[8];
	float Sea_Level_Pressure;
	uint16_t C1;
	    uint16_t C2;
	    uint16_t C3;
	    uint16_t C4;
	    uint16_t C5;
	    uint16_t C6;
}MS580301;

void MS580301_Init(MS580301* sensor, I2C_HandleTypeDef* hi2c);
void MS580301_Reset(MS580301* sensor);
void MS580301_ReadCalibrationData(MS580301* sensor);
void MS580301_ReadSensorData(MS580301* sensor, uint32_t* pressure, uint32_t* temperature);




#endif /* INC_MS580301_H_ */
