#include "aht20.h"

#define AHT20_ADDRESS 0x70

HAL_StatusTypeDef AHT20_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t readBuffer;
    HAL_Delay(40);

    HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(hi2c, AHT20_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);
    if (ret != HAL_OK) {
        return ret;
    }

    if ((readBuffer & 0x08) == 0x00) {
        uint8_t sendBuffer[3] = { 0xBE, 0x08, 0x00 };
        ret = HAL_I2C_Master_Transmit(hi2c, AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
    }
    return ret;
}
void AHT20_Read(float *Temperature, float *Humidity){
	uint8_t sendBuffer[3] = { 0xAC, 0x33, 0x00 };
	uint8_t readBuffer[6];

	HAL_I2C_Master_Transmit(&hi2c2,  AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
	HAL_Delay(75);

	HAL_I2C_Master_Receive(&hi2c2,  AHT20_ADDRESS, readBuffer, 6, HAL_MAX_DELAY);
	if((readBuffer[0] & 0x80) == 0x00){
		uint32_t data = 0;
	data = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
	*Humidity = data * 100.0f / (1 << 20);

	data = (((uint32_t)readBuffer[3] & 0x0F) << 16) + ((uint32_t)readBuffer[4] << 8) + (uint32_t)readBuffer[5];
	*Temperature = data * 200.0f / (1 << 20) - 50;
	}
}
/*
HAL_StatusTypeDef AHT20_Read(I2C_HandleTypeDef *hi2c, float *Temperature, float *Humidity) {
    uint8_t sendBuffer[3] = { 0xAC, 0x33, 0x00 };
    uint8_t readBuffer[6];
    HAL_StatusTypeDef ret;

    ret = HAL_I2C_Master_Transmit(hi2c, AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
    if (ret != HAL_OK) {
        return ret;
    }

    HAL_Delay(75);

    ret = HAL_I2C_Master_Receive(hi2c, AHT20_ADDRESS, readBuffer, 6, HAL_MAX_DELAY);
    if (ret != HAL_OK) {
        return ret;
    }

    if ((readBuffer[0] & 0x80) == 0x00) {
        uint32_t data = 0;
        data = ((uint32_t)readBuffer[1] << 12) | ((uint32_t)readBuffer[2] << 4) | ((uint32_t)(readBuffer[3] >> 4));
        *Humidity = data * 100.0f / 1048576.0f;

        data = (((uint32_t)(readBuffer[3] & 0x0F)) << 16) | ((uint32_t)readBuffer[4] << 8) | ((uint32_t)readBuffer[5]);
        *Temperature = (data * 200.0f / 1048576.0f) - 50.0f;
    }

    return HAL_OK;
} */
/*
void AHT20_Init(){
		uint8_t readBuffer;
	HAL_Delay(40);
	HAL_I2C_Master_Receive(&hi2c2,  AHT20_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);
	if ((readBuffer & 0x08) == 0x00){
		uint8_t sendBuffer[3] = { 0xBE, 0x08, 0x00};
		HAL_I2C_Master_Transmit(&hi2c2,  AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
	}



void AHT20_Read(float *Temperature, float *Humidity){
	uint8_t sendBuffer[3] = { 0xAC, 0x33, 0x00 };
	uint8_t readBuffer[6];

	HAL_I2C_Master_Transmit(&hi2c2,  AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
	HAL_Delay(75);
	HAL_I2C_Master_Receive(&hi2c2,  AHT20_ADDRESS, readBuffer, 6, HAL_MAX_DELAY);

	if((readBuffer[0] & 0x80) == 0x00){
		uint32_t data = 0;
		data = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
		*Humidity = data * 100.0f / (1 << 20);

		data = (((uint32_t)readBuffer[3] & 0x0F) << 16) + ((uint32_t)readBuffer[4] << 8) + (uint32_t)readBuffer[5];
		*Temperature = data * 200.0f / (1 << 20) - 50;
	}

}
*/
