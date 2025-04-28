/*
 * aht20.h
 *
 *  Created on: Apr 9, 2025
 *      Author: irvin
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_
#include "stm32l4xx_hal.h"
#include "i2c.h"

//void AHT20_Init();
HAL_StatusTypeDef AHT20_Init(I2C_HandleTypeDef *hi2c);
//HAL_StatusTypeDef AHT20_Read(I2C_HandleTypeDef *hi2c, float *Temperature, float *Humidity);
void AHT20_Read(float *Temperature, float *Humidity);
//void AHT20_Read(float *Temperature, float *Humidity);

#endif /* INC_AHT20_H_ */
