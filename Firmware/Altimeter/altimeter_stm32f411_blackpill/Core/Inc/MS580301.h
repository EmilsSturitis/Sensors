/*
 * ms5.h
 *
 *  Created on: Feb 17, 2023
 *      Author: emils
 */

#ifndef INC_MS580301_H_
#define INC_MS580301_H_

#include "stm32f4xx_hal.h"


#define MS580301_I2C_ADDR 	(0x76 << 1) //CBS setting high

/*
 * Registers
 *
 */

#define MS580301_REG_RESET				0x1E	//Reset
#define MS580301_REG_CONVERT_D1_256		0x40	//Convert Digital Pressure value OSR=256
#define MS580301_REG_CONVERT_D1_512		0x42	//Convert Digital Pressure value OSR=512
#define MS580301_REG_CONVERT_D1_1024	0x44	//Convert Digital Pressure value OSR=1024
#define MS580301_REG_CONVERT_D1_2048	0x46	//Convert Digital Pressure value OSR=2048
#define MS580301_REG_CONVERT_D1_4096	0x48	//Convert Digital Pressure value OSR=4096
#define MS580301_REG_CONVERT_D2_256		0x50	//Convert Digital temperature value OSR=256
#define MS580301_REG_CONVERT_D2_512		0x52	//Convert Digital temperature value OSR=512
#define MS580301_REG_CONVERT_D2_1024	0x54	//Convert Digital temperature value OSR=1024
#define MS580301_REG_CONVERT_D2_2048	0x56	//Convert Digital temperature value OSR=2048
#define MS580301_REG_CONVERT_D2_4096	0x58	//Convert Digital temperature value OSR=4096
#define MS580301_REG_ADC_READ			0x00	//ADC read
#define MS580301_REG_PROM_READ_000		0xA0	//16 bits reserved from manufacturer
#define MS580301_REG_PROM_READ_001		0xA2	//Coefficient 1, Pressure sensitivity
#define MS580301_REG_PROM_READ_010		0xA4	//Coefficient 2, Pressure offset
#define MS580301_REG_PROM_READ_011		0xA6	//Coefficient 3, Temperature coefficient of pressure sensitivity
#define MS580301_REG_PROM_READ_100		0xA8	//Coefficient 4, Temperature coefficient of pressure offset
#define MS580301_REG_PROM_READ_101		0xAA	//Coefficient 5, Reference temperature
#define MS580301_REG_PROM_READ_110		0xAC	//Coefficient 6, Temperature coefficient of the temperature
#define MS580301_REG_PROM_READ_111		0xAE	//CRC CRC-4 used


/*
 * Sensor struct
 */

typedef struct {
	//i2c handle
	I2C_HandleTypeDef *i2cHandle;

	//pressure data in milibars
	unsigned int press_mbar;

	// temp data in celsius
	unsigned int temp_C;

	// augstums
	signed int hight_m;




}MS580301;

/*
 * Initialisation
 *
 */

uint8_t MS580301_Initialise( MS580301 *dev, I2C_HandleTypeDef *i2cHandle );

/*
 * Data aqusition
 */

HAL_StatusTypeDef MS580301_ReadPressure( MS580301 *dev );
HAL_StatusTypeDef MS580301_ReadTemperature( MS580301 *dev );

HAL_StatusTypeDef MS580301_Coefficient1( MS580301 *dev );
HAL_StatusTypeDef MS580301_Coefficient2( MS580301 *dev );
HAL_StatusTypeDef MS580301_Coefficient3( MS580301 *dev );
HAL_StatusTypeDef MS580301_Coefficient4( MS580301 *dev );
HAL_StatusTypeDef MS580301_Coefficient5( MS580301 *dev );
HAL_StatusTypeDef MS580301_Coefficient6( MS580301 *dev );

/*
 * Low level functions
 */

HAL_StatusTypeDef MS580301_ReadRegister( MS580301 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MS580301_ReadRegisters( MS580301 *dev, uint8_t reg, uint8_t *data, uint8_t *lenght );

HAL_StatusTypeDef MS580301_WriteRegister( MS580301 *dev, uint8_t reg, uint8_t *data);



#endif /* INC_MS580301_H_ */
