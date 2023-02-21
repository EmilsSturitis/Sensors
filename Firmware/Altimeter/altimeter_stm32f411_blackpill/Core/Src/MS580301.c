/*
 * ms5.c
 *
 *  Created on: Feb 17, 2023
 *      Author: emils
 */
#include "MS580301.h"
/*
 * Init
 */
uint8_t MS580301_Initilise( MS580301 *dev, I2C_HandleTypeDef *i2cHandle)
{
	// Set struct parameters
	dev->i2cHandle		=i2cHandle;
	// parametri kurus gribu dabūt no sensora todo
	dev -> press_mbar	=	0.0f;
	dev -> temp_C		=	0.0f;
	dev -> hight_m		=	0.0f;



	// Store number of transatction errors
	uint8_t errNum = 0;
	HAL_StatusTypeDef status;


	/*
	 *read Coefficients
	 */

	/*
	 * Store coefficients
	 */
}

/*
 * Data acquisition
 */
// 24 bits
HAL_StatusTypeDef MS580301_ReadPressure( MS580301 *dev)
{
	// write to register

	HAL_StatusTypeDef status = MS580301_WriteRegister( dev, MS580301_REG_CONVERT_D1_4096);

	uint8_t regData[3];

	// read adc
	HAL_StatusTypeDef status = MS580301_ReadRegisters(dev, MS580301_REG_ADC_READ, regData, 3);
	// set mode to be read

	uint32_t PressureRaw = ( ((regData[0] & 0x0F) << 8) | regData[2] );

	//dev-> press =
	return status;



	// read from register
}
//24 bits
HAL_StatusTypeDef MS580301_ReadTemperature( MS580301 *dev)
{
	// set mode to be read


	// read adc
}

/*
 * Low level functions
 */

HAL_StatusTypeDef MS580301_ReadRegister( MS580301 *dev, uint8_t reg, uint8_t *data)
{
	return HAL_I2C_Mem_Read( dev->i2cHandle, MS580301_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY );
}

HAL_StatusTypeDef MS580301_ReadRegisters( MS580301 *dev, uint8_t reg, uint8_t *data, uint8_t lenght)
{
	return HAL_I2C_Mem_Read( dev->i2cHandle, MS580301_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, lenght, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MS580301_WriteRegister( MS580301 *dev, uint8_t reg, uint8_t *data)
{
	return HAL_I2C_Mem_Write( dev->i2cHandle, MS580301_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}
